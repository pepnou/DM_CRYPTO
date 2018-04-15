#include <gmp.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Jacobi.h"


int Jacobi(mpz_t a, mpz_t n)
{
	int res;
		
	if(!mpz_cmp_ui(a,2))
	{
		if(mpz_congruent_ui_p(n,1,8) || mpz_congruent_ui_p(n,7,8))
			res = 1;
		else
			res = -1;
	}
	else if(mpz_even_p(a))
	{
		mpz_t b, n2;
		mpz_init(b);
		mpz_init(n2);
		mpz_set_ui(b,2);
		mpz_set(n2,n);
		
		mpz_tdiv_q_2exp(a,a,1);
		res = Jacobi(a,n)*Jacobi(b,n2);
		
		mpz_clear(b);
		mpz_clear(n2);
	}
	else if(!mpz_cmp_ui(a,1))
	{
		res = 1;
	}
	else if(!Prime(a,n))
	{
		res = 0;
	}
	else
	{
		if(mpz_congruent_ui_p(a,1,4) || mpz_congruent_ui_p(n,1,4))
			res = 1;
		else
			res = -1;
		
		mpz_mod(n,n,a);
		res *= Jacobi(n,a);
	}
	
	return res;
}

bool Prime(mpz_t a, mpz_t b)
{
	bool prime;
	mpz_t res;
	mpz_init(res);
	
	Euclide(a,b,res);
	
	if(!mpz_cmp_ui(res,1))
		prime = true;
	else
		prime = false;
	
	mpz_clear(res);
	
	return prime;
}

void Euclide(mpz_t a, mpz_t b, mpz_t res)
{
	mpz_t r;
	mpz_init(r);
	
	mpz_mod(r,a,b);
	
	while(!mpz_cmp_ui(r,0))
	{
		mpz_set(a,b);
		mpz_set(b,r);
		mpz_mod(r,a,b);
	}
	
	mpz_set(res,b);
	
	mpz_clear(r);
}
