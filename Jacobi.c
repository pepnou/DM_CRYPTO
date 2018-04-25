#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Jacobi.h"

//Calcul du symbol de Jacobi
//renvoi (a/n)
int Jacobi(mpz_t a, mpz_t n)
{
	int res;
	mpz_t b, n2;
		
	if(!mpz_cmp_ui(a,2)) // Propriété n°2
	{
		if(mpz_congruent_ui_p(n,1,8) || mpz_congruent_ui_p(n,7,8))
			res = 1;
		else
			res = -1;
	}
	else if(!mpz_tstbit(a,0)) // Propriété n°3 (si le 1er bit est 1 alors a est pair)
	{
		mpz_inits(b,n2,NULL);
		mpz_set_ui(b,2);
		mpz_set(n2,n);
		
		mpz_divexact_ui(a,a,2);
		res = Jacobi(a,n)*Jacobi(b,n2);
		
		mpz_clears(b,n2,NULL);
	}
	else if(!mpz_cmp_ui(a,1)) // Propriété n°4
	{
		res = 1;
	}
	else if(!Prime(a,n)) // Propriété n°2
	{
		res = 0;
	}
	else // Propriété n°6 et Propriété n°1 (Dans notre cas, si on calcule (a/b), a est tjr plus petit que b, sauf si on applique la propriété 6)
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

//Test si 2 nombre sont premier entre eux
//renvoi vrai si pgcd(a,b)=1, faux sinon
bool Prime(mpz_t a, mpz_t b)
{
	bool prime;
	mpz_t res, a_c, b_c;
	mpz_inits(res, a_c, b_c, NULL);
	
	mpz_set(a_c,a);
	mpz_set(b_c,b);
	
	//Comme le type mpz_t est une addresse, on doit copier les valeurs, sans quoi elles seraient modifiées dans le reste du programme
	Euclide(a_c,b_c,res); // res = pgcd(a,b)
	
	if(!mpz_cmp_ui(res,1)) //si le pgcd est 1
		prime = true;
	else
		prime = false;
	
	mpz_clears(res, a_c,b_c, NULL);
	
	return prime;
}

//Calcul du pgcd avec l'algorithme d'Euclide
//res = pgcd(a,b)
void Euclide(mpz_t a, mpz_t b, mpz_t res)
{
	
	mpz_t r;
	mpz_init(r);
	
	mpz_mod(r,a,b);
	
	while(mpz_cmp_ui(r,0)) //Tant que le reste n est pas nul
	{
		mpz_set(a,b); // a = b
		mpz_set(b,r); // b = r
		mpz_mod(r,a,b); // r = a % b
	}
	
	mpz_set(res,b);
	mpz_clear(r);
}
