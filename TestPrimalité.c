#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "TestPrimalité.h"


int main(int argc, char** argv)
{
	//~ mpz_t nombre;
	//~ mpz_init(nombre);
	//~ int k;
	
	//~ Lecture(argv[1],atoi(argv[2]),nombre);
	//~ gmp_printf("%Zd\n",nombre);
	
	
	
	//~ mpz_t a,H,n,res;
	//~ mpz_init(a);
	//~ mpz_init(H);
	//~ mpz_init(n);
	//~ mpz_init(res);
	
	//~ mpz_set_ui(a,428);
	//~ mpz_set_ui(H,165);
	//~ mpz_set_ui(n,46);
	
	//~ Expo(a,H,n,res);
	
	//~ gmp_printf("%Zd\n",res);
	
	//~ mpz_clear(a);
	//~ mpz_clear(H);
	//~ mpz_clear(n);
	//~ mpz_clear(res);
	
	/*switch(argc)
	{
		case 2:
			
			break;
		case 3:
			k = atoi(argv[2]);
			
			AfficherRes(SolovayStrassen(nombre,k),nombre,k);
			break;
		case 4:
			k = atoi(argv[3]);
			Lecture(argv[1],atoi(argv[2]),nombre);
			AfficherRes(SolovayStrassen(nombre,k),nombre,k);
			break;
		default:
			
			break;
	}*/
	
	return 0;
}

bool SolovayStrassen(mpz_t n,int k)
{
	bool res = true;
	
	gmp_randstate_t state;
	gmp_randinit_default(state);
	
	mpz_t a, exp, r, H;
	mpz_init(a);
	mpz_init(exp);
	mpz_init(r);
	mpz_init(H);
		
	for(;k>0;k--)
	{
		mpz_sub_ui(a,n,2);
		mpz_urandomm(a,state,a);
		mpz_add_ui(a,a,2);
		
		mpz_set_ui(r,Jacobi(a,n));
		if(!mpz_cmp_ui(r,0))
			res = false;
		else
		{
			mpz_sub_ui(H,n,1);
			mpz_fdiv_q_ui(H,H,2);
			
			Expo(a,H,n,exp);
			
			if(!mpz_congruent_p(exp,r,n))
				res = false;
		}
	}
	
	mpz_clear(a);
	mpz_clear(exp);
	mpz_clear(r);
	mpz_clear(H);
	return res;
}

void AfficherRes(bool b, mpz_t n, int k)
{
	
}

