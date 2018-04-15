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
	
	
	
	mpz_t a,H,n,res;
	mpz_init(a);
	mpz_init(H);
	mpz_init(n);
	mpz_init(res);
	
	mpz_set_ui(a,428);
	mpz_set_ui(H,165);
	mpz_set_ui(n,46);
	
	Expo(a,H,n,res);
	
	gmp_printf("%Zd\n",res);
	
	mpz_clear(a);
	mpz_clear(H);
	mpz_clear(n);
	mpz_clear(res);
	
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
	gmp_randstate_t state;
	gmp_randinit_default(state);
	
	mpz_t a;
	mpz_init(a);
	for(;k>0;k--)
	{
		mpz_sub_ui(a,n,2);
		mpz_urandomm(a,state,a);
		mpz_add_ui(a,a,2);
		
		if(!Jacobi(a,n))
		{
			mpz_clear(a);
			return false;
		}
	}
	mpz_clear(a);
	return true;
}

void AfficherRes(bool b, mpz_t n, int k)
{
	
}

