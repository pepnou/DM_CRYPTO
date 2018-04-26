#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "TestPrimalité.h"


int main(int argc, char** argv)
{
	mpz_t n;
	mpz_init(n);
	
	//récupération des arguments
	struct arguments arguments;
	argp_parse (&argp, argc, argv, 0, 0, &arguments);
	
	if(arguments.input_file)
	{
		Lecture(arguments.input_file, arguments.index, arguments.base, n);
	}
	else
	{		
		if(mpz_set_str(n,arguments.number,arguments.base) == -1)
		{
			printf("The number is not valid in the specified base\n");
			exit(-1);
		}
	}
	
	if(arguments.base<2)
	{
		printf("Base must be higher than 1\n");
		exit(-1);
	}
	else if(arguments.base>62)
	{
		printf("Base must be lower than 63\n");
		exit(-1);
	}
		
	AfficherRes(SolovayStrassen(n,arguments.repetitions),n,arguments.repetitions, arguments.base, arguments.verbose);
	
	mpz_clear(n);
	return 0;
}


//effectue le test de primalité Solovay-Strassen
//renvoi vrai si 'n' est peut etre premier apres 'k' répétitions
bool SolovayStrassen(mpz_t n, int k)
{	
	bool res = true;
	
	//Comme le nombre aléatoire est compris entre 2 et n-1, ont doit d'abord
	//verifier si 'n' n est pas égal a 1, 2 ou 3 pour eviter les erreur
	//lors de la selection du nombre aléatoire 
	if((!mpz_cmp_ui(n,1)) || (!mpz_cmp_ui(n,2)) || (!mpz_cmp_ui(n,3)))
		return true;
	//si 'n' est pair il n est pas premier
	if(!mpz_tstbit(n,0))
		return false;
	
	gmp_randstate_t state;
	gmp_randinit_default(state);
	
	mpz_t a, exp, r, H;
	mpz_inits(a, exp, r, H, NULL);
	
	mpz_fdiv_q_ui(H,n,2); //H = (n-1)/2 ,le -1 est implicite dans fdiv si n est impair
		
	for(;k>0;k--)
	{
		mpz_sub_ui(a,n,3);
		// a = n-3
		mpz_urandomm(a,state,a);
		// 0 <= a <= n-3
		mpz_add_ui(a,a,2);
		// 2 <= a <= n-1
		
		mpz_set_si(r,Jacobi(a,n)); //r = ( a / n )

		if(!mpz_cmp_ui(r,0))
			res = false;
		else
		{
			Expo(a,H,n,exp); // exp = a^H % n
			
			// si (a / n) n est pas congru a a^((n-1)/1)%n
			if(!mpz_congruent_p(exp,r,n))
				res = false;
		}
	}
	
	mpz_clears(a, exp, r, H, NULL);
	
	return res;
}



