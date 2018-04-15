#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#include "Exponentiation.h"


void Expo(mpz_t a, mpz_t H, mpz_t n, mpz_t res)
{
	int i = mpz_sizeinbase(H,2) -1;
	
	mpz_set(res,a);
	
	while(i)
	{
		mpz_mul(res,res,res);
		if(mpz_tstbit(H,i-1))
		{
			mpz_mul(res,res,a);
		}
		mpz_mod(res,res,n);
		i--;
	}
}
