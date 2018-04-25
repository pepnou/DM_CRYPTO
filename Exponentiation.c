#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#include "Exponentiation.h"

//fct d'exponentiation rapide
//res = a^H % n
void Expo(mpz_t a, mpz_t H, mpz_t n, mpz_t res)
{
	int i = mpz_sizeinbase(H,2) -1; // i = nbr bit de H, - 1 car les bit sont indicés a partir de 0
	
	mpz_set(res,a); // res = a
	
	while(i) //on parcours les bit de H
	{
		mpz_mul(res,res,res); //res = res²
		if(mpz_tstbit(H,i-1)) //si le i-1 ieme bit est a un
		{
			mpz_mul(res,res,a); // res = res * a
		}
		mpz_mod(res,res,n); // res = res % n
		i--;
	}
}
