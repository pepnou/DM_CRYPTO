#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "TestPrimalité.h"


int main(int argc, char** argv)
{
	int k;
	mpz_t n;
	
	mpz_init(n);
	
	//~ mpz_set_ui(n,5);
	Lecture("./test/nbr_premier.txt",2,n);
	k = 50;
	
	int tmp1 = SolovayStrassen(n,k);
	int tmp2 = mpz_probab_prime_p(n,k);
	gmp_printf("%Zd %d\n%d\n%d\n\n",n,k,tmp1,tmp2);
	
	mpz_clear(n);
	
	return 0;
}

bool SolovayStrassen(mpz_t n, int k)
{
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
		
		mpz_set_si(r,Jacobi(a,n));
		
		if(!mpz_cmp_ui(r,0))
			res = false;
		else
		{
			Expo(a,H,n,exp);
						
			if(!mpz_congruent_p(exp,r,n))
				res = false;
		}
	}
	
	mpz_clears(a, exp, r, H, NULL);
	
	return res;
}

void AfficherRes(bool b, mpz_t n, int k)
{
	
}

