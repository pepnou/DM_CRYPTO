#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "TestPrimalité.h"


int main(int argc, char** argv)
{
	clock_t deb = clock(), fin;
	
	mpz_t n;
	
	mpz_init(n);
	
	//~ mpz_set_ui(n,5);
	//~ Lecture("./test/nbr_premier.txt",2,n);
	
	//int tmp1 = SolovayStrassen(n,k);
	//int tmp2 = mpz_probab_prime_p(n,k);
	//gmp_printf("%Zd %d\n%d\n%d\n\n",n,k,tmp1,tmp2);
		
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
			printf("le nombre à tester n est pas valide dans la base spécifiée\n");
			exit(-1);
		}
	}
	
	AfficherRes(SolovayStrassen(n,arguments.repetitions),n,arguments.repetitions, arguments.base, arguments.verbose);
	
	mpz_clear(n);
	
	fin = clock();
	
	printf("temp total = %f\n",(double)(fin - deb) / CLOCKS_PER_SEC);
	
	return 0;
}

bool SolovayStrassen(mpz_t n, int k)
{
	clock_t t_jac = 0, t_exp = 0, t_jac2 = 0, t_deb, t_fin;
	
	bool res = true;
	
	if(mpz_even_p(n))
		return false;
	if(!mpz_cmp_ui(n,3))
		return true;
	
	gmp_randstate_t state;
	gmp_randinit_default(state);
	
	mpz_t a, exp, r, H;
	mpz_inits(a, exp, r, H, NULL);
	
	mpz_fdiv_q_ui(H,n,2);
		
	for(;k>0;k--)
	{
		mpz_sub_ui(a,n,3);
		mpz_urandomm(a,state,a);
		mpz_add_ui(a,a,2);
		
		t_deb = clock();
		mpz_set_si(r,Jacobi(a,n));
		t_fin = clock();
		t_jac += (t_fin - t_deb);
		gmp_printf("%Zd\n",r);
		
		
		t_deb = clock();
		printf("%d\n",mpz_jacobi(a,n));
		t_fin = clock();
		t_jac2 += (t_fin - t_deb);
		
		if(!mpz_cmp_ui(r,0))
			res = false;
		else
		{
			t_deb = clock();
			Expo(a,H,n,exp);
			t_fin = clock();
			t_exp += (t_fin - t_deb);
			
			if(!mpz_congruent_p(exp,r,n))
				res = false;
		}
	}
	
	mpz_clears(a, exp, r, H, NULL);
	
	//~ t_jac = (double) t_jac/CLOCKS_PER_SEC;
	//~ t_exp = (double) t_exp/CLOCKS_PER_SEC;
	
	printf("t jacobi = %f\n",(double) t_jac/CLOCKS_PER_SEC);
	printf("t jacobi 2 = %f\n",(double) t_jac2/CLOCKS_PER_SEC);
	printf("t exponentiation = %f\n",(double) t_exp/CLOCKS_PER_SEC);
	
	return res;
}



