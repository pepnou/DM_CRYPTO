#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Jacobi.h"


int Jacobi(mpz_t a, mpz_t n)
{
	
	
	//gmp_printf("Jacobi : ( %Zd / %Zd )\n",a,n);
	int res;
	mpz_t b, n2;
		
	if(!mpz_cmp_ui(a,2))
	{
		if(mpz_congruent_ui_p(n,1,8) || mpz_congruent_ui_p(n,7,8))
			res = 1;
		else
			res = -1;
	}
	else if(mpz_even_p(a))
	{
		mpz_inits(b,n2,NULL);
		mpz_set_ui(b,2);
		mpz_set(n2,n);
		
		mpz_tdiv_q_2exp(a,a,1);
		res = Jacobi(a,n)*Jacobi(b,n2);
		
		mpz_clears(b,n2,NULL);
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
		
		mpz_init(n2);
		mpz_mod(n2,n,a);
		res *= Jacobi(n2,a);
		mpz_clear(n2);
	}
	
	return res;
}

bool Prime(mpz_t a, mpz_t b)
{
	bool prime;
	mpz_t res, a_c, b_c;
	mpz_inits(res, a_c, b_c, NULL);
	
	mpz_set(a_c,a);
	mpz_set(b_c,b);
	
	Euclide(a_c,b_c,res);
	
	if(!mpz_cmp_ui(res,1))
		prime = true;
	else
		prime = false;
	
	mpz_clears(res, a_c,b_c, NULL);
	
	return prime;
}

void Euclide(mpz_t a, mpz_t b, mpz_t res)
{
	mpz_t r, a_c, b_c;
	mpz_inits(r, a_c, b_c, NULL);
	
	mpz_set(a_c,a);
	mpz_set(b_c,b);
	mpz_mod(r,a_c,b_c);
	
	while(mpz_cmp_ui(r,0))
	{
		mpz_set(a_c,b_c);
		mpz_set(b_c,r);
		mpz_mod(r,a_c,b_c);
	}
	
	mpz_set(res,b_c);
	mpz_clears(r, a_c,b_c, NULL);
}
