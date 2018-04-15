#include <gmp.h>
#include <stdlib.h>

#include "Jacobi.h"


int Jacobi(mpz_t a, mpz_t n)
{
	int res = 1;
	
	mpz_mod(a,a,n); //--- (1)
	
	return res;
}
