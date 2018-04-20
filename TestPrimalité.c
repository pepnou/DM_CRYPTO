#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <sys/ioctl.h>


#include "TestPrimalité.h"

int main(int argc, char** argv)
{	
	mpz_t n;
	
	mpz_init(n);
	
	//~ mpz_set_ui(n,5);
	//~ Lecture("./test/nbr_premier.txt",2,n);
	
	//int tmp1 = SolovayStrassen(n,k);
	//int tmp2 = mpz_probab_prime_p(n,k);
	//gmp_printf("%Zd %d\n%d\n%d\n\n",n,k,tmp1,tmp2);
		
	struct arguments arguments;
	argp_parse (&argp, argc, argv, 0, 0, &arguments);
	
	if(arguments.input_file)
	{
		Lecture(arguments.input_file, arguments.index, arguments.base, n);
	}
	else
	{		
		if(mpz_set_str(n,arguments.number,arguments.base) == -1)
		{
			printf("le nombre à tester n est pas valide dans la base spécifiée\n");
			exit(-1);
		}
	}
	
	AfficherRes(SolovayStrassen(n,arguments.repetitions),n,arguments.repetitions, arguments.base, arguments.verbose);
	
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

#define RED   "\x1B[1;31m"
#define GRN   "\x1B[1;32m"
#define YEL   "\x1B[1;33m"
#define BLU   "\x1B[1;34m"
#define MAG   "\x1B[1;35m"
#define CYN   "\x1B[1;36m"
#define WHT   "\x1B[1;37m"

#define RED_B   "\x1B[1;41m"
#define GRN_B   "\x1B[1;42m"
#define YEL_B   "\x1B[1;43m"
#define BLU_B   "\x1B[1;44m"
#define MAG_B   "\x1B[1;45m"
#define CYN_B   "\x1B[1;46m"
#define WHT_B   "\x1B[1;47m"

#define RESET "\x1B[0m"

void AfficherRes(bool b, mpz_t n, int k, int base, bool v)
{
	system("clear");
	
	//~ printf(RED "\x1B[78Cred\n" RESET);
	//~ printf(GRN "green\n" RESET);
	//~ printf(YEL "yellow\n" RESET);
	//~ printf(BLU "blue\n" RESET);
	//~ printf(MAG "magenta\n" RESET);
	//~ printf(CYN "cyan\n" RESET);
	//~ printf(WHT "white\n" RESET);
	
	//~ printf(RED_B "red\n" RESET);
	//~ printf(GRN_B "green\n" RESET);
	//~ printf(YEL_B "yellow\n" RESET);
	//~ printf(BLU_B "blue\n" RESET);
	//~ printf(MAG_B "magenta\n" RESET);
	//~ printf(CYN_B "cyan\n" RESET);
	//~ printf(WHT_B "white\n" RESET);
		
	if(!v)
	{
		if(b)
			printf("Prime\n");
		else
			printf("Not Prime\n");
		exit(0);
	}
	
	struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    char* nbr = mpz_get_str(NULL,base,n), temp[w.ws_col];
    int i, offset = w.ws_col - 2*3, tmp;
    
    for(i=0;i<w.ws_col;i++)
		printf(GRN "#" RESET);
	printf(GRN "\n#\x1B[%dC#\n" RESET,w.ws_col-2);
	
	sprintf(temp,"Number in base %d :",base);
	printf(GRN "# " RED "%s" GRN "\x1B[%ldC #\n" RESET,temp,w.ws_col - 2*2 - strlen(temp));
	
	i = 0;
	while(i < strlen(nbr))
	{
		tmp = nbr[i + offset];
		nbr[i + offset] = '\0';
		printf(GRN "#  " RESET "%s",&nbr[i]);
		
		if(strlen(&nbr[i]) < offset)
			printf(GRN "\x1B[%ldC  #\n" RESET,offset - strlen(&nbr[i]));
		else
			printf(GRN "  #\n" RESET);
				
		nbr[i + offset] = tmp;
		i+= offset;
	}
	
	printf(GRN "#\x1B[%dC#\n" RESET,w.ws_col-2);
	sprintf(temp,"Repetitions :",base);
	printf(GRN "# " RED "%s" GRN "\x1B[%ldC #\n" RESET,temp,w.ws_col - 2*2 - strlen(temp));
	
	sprintf(temp,"%d",k);
	printf(GRN "#  "RESET"%s\x1B[%ldC"GRN"  #\n" RESET,temp,w.ws_col - 2*3 - strlen(temp));
	
	printf(GRN "#\x1B[%dC#\n" RESET,w.ws_col-2);
	sprintf(temp,"Prime ?",base);
	printf(GRN "# " RED "%s" GRN "\x1B[%ldC #\n" RESET,temp,w.ws_col - 2*2 - strlen(temp));
	
	sprintf(temp,"%s",b?"Yes":"No");
	printf(GRN "#  "RESET"%s\x1B[%ldC"GRN"  #\n" RESET,temp,w.ws_col - 2*3 - strlen(temp));
	
	double proba = 1 - ldexp(1,-k);
	
	printf(GRN "#\x1B[%dC#\n" RESET,w.ws_col-2);
	sprintf(temp,"Probability :",base);
	printf(GRN "# " RED "%s" GRN "\x1B[%ldC #\n" RESET,temp,w.ws_col - 2*2 - strlen(temp));
	
	sprintf(temp,"%.25lf",proba);
	printf(GRN "#  "RESET"%s\x1B[%ldC"GRN"  #\n" RESET,temp,w.ws_col - 2*3 - strlen(temp));
	
			
	printf(GRN "#\x1B[%dC#\n" RESET,w.ws_col-2);
	for(i=0;i<w.ws_col;i++)
		printf(GRN "#" RESET);
	printf("\n");
}

