#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "TestPrimalité.h"


int main(int argc, char** argv)
{
	int k;
	
	mpz_t a,b,c,n,res;
	
	mpz_inits(a,b,c,n,res,NULL);
	
	mpz_set_ui(a,413);
	mpz_set_ui(b,127);
	mpz_set_ui(c,64);
	
	//~ mpz_set_ui(n,3);
	Lecture("./test/nbr_premier.txt",1,n);
	k = 50;
	
	mpz_fdiv_q_ui(res,b,2);
	gmp_printf("%Zd\n\n",res);
	
	gmp_printf("%Zd %Zd %Zd\n",a,b,c);
	Expo(a,b,c,res);
	gmp_printf("%Zd\n",res);
	mpz_powm(res,a,b,c);
	gmp_printf("%Zd\n\n",res);
	
	
	gmp_printf("%Zd %Zd\n%d\n%d\n\n",a,b,Jacobi(a,b),mpz_jacobi(a,b));
	
	
	gmp_printf("%Zd %Zd\n",a,b);
	Euclide(a,b,res);
	gmp_printf("%Zd\n",res);
	mpz_gcd(res,a,b);
	gmp_printf("%Zd\n\n",res);
	
	
	gmp_printf("%Zd %Zd\n%d\n\n",a,b,Prime(a,b));
	
	
	debug
	int tmp1 = SolovayStrassen(n,k);
	debug
	int tmp2 = mpz_probab_prime_p(n,k);
	debug
	gmp_printf("%Zd %d\n%d\n%d\n\n",n,k,tmp1,tmp2);
	
	
	mpz_clears(a,b,c,n,res,NULL);
	
	return 0;
}

bool SolovayStrassen(mpz_t n, int k)
{
	bool res = true;
	
	if(mpz_even_p(n))
		return false;
	
	gmp_randstate_t state;
	gmp_randinit_default(state);
	
	mpz_t a, exp, r, H;
	mpz_inits(a, exp, r, H, NULL);
	
	for(;k>0;k--)
	{
		mpz_sub_ui(a,n,3);
		mpz_urandomm(a,state,a);
		mpz_add_ui(a,a,2);
		
		mpz_set_ui(r,Jacobi(a,n));
		
		if(Jacobi(a,n) != mpz_jacobi(a,n))
			gmp_printf("%Zd %Zd\n\n",a,n);
		
		if(!mpz_cmp_ui(r,0))
			res = false;
		else
		{
			//mpz_sub_ui(H,n,1);
			mpz_fdiv_q_ui(H,H,2);
			
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

