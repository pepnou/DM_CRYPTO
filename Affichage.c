#include <string.h>
#include <sys/ioctl.h>
#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "Affichage.h"

#define RED   "\x1B[1;31m"
#define GRN   "\x1B[1;32m"
#define RESET "\x1B[0m"

//affiche le résultat du test de primalité
//depend de l'option -v (passée en paramètre dans v)
void AfficherRes(bool b, mpz_t n, int k, int base, bool v)
{
	system("clear");
		
	if(!v)
	{
		if(b)
			printf("Prime\n");
		else
			printf("Not Prime\n");
		exit(0);
	}
	
	struct winsize w;
    ioctl(0, TIOCGWINSZ, &w); //récupère la taille du terminal
    char* nbr = mpz_get_str(NULL,base,n), temp[w.ws_col], tmp;
    int i, offset = w.ws_col - 2*3, offset2 = w.ws_col - 2*2;
    
    for(i=0;i<w.ws_col;i++)
		printf(GRN "#" RESET);
	printf(GRN "\n#\x1B[%dC#\n" RESET,w.ws_col-2); //utise les séquences
//  d'échappement ANSI afin de déplacer le curseur ou de changer la
//  couleur d'écriture
	
	sprintf(temp,"Number in base %d :",base);
	printf(GRN "# " RED "%s" GRN "\x1B[%ldC #\n" RESET,temp,offset2 - strlen(temp));
	
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
	
	//afiche la taille dans la base précisée par l'option -b
	printf(GRN "#\x1B[%dC#\n" RESET,w.ws_col-2);
	sprintf(temp,"Size in base %d :",base);
	printf(GRN "# " RED "%s" GRN "\x1B[%ldC #\n" RESET,temp,offset2 - strlen(temp));
	
	sprintf(temp,"%ld",mpz_sizeinbase(n,base));
	printf(GRN "#  "RESET"%s\x1B[%ldC"GRN"  #\n" RESET,temp,offset - strlen(temp));
	
	
	//affiche la taille en base 2
	printf(GRN "#\x1B[%dC#\n" RESET,w.ws_col-2);
	sprintf(temp,"Size in base 2 :");
	printf(GRN "# " RED "%s" GRN "\x1B[%ldC #\n" RESET,temp,offset2 - strlen(temp));
	
	sprintf(temp,"%ld",mpz_sizeinbase(n,2));
	printf(GRN "#  "RESET"%s\x1B[%ldC"GRN"  #\n" RESET,temp,offset - strlen(temp));
	
	
	//affiche le nombre de répétitions
	printf(GRN "#\x1B[%dC#\n" RESET,w.ws_col-2);
	sprintf(temp,"Repetitions :");
	printf(GRN "# " RED "%s" GRN "\x1B[%ldC #\n" RESET,temp,offset2 - strlen(temp));
	
	sprintf(temp,"%d",k);
	printf(GRN "#  "RESET"%s\x1B[%ldC"GRN"  #\n" RESET,temp,offset - strlen(temp));
	
	
	//affiche le résultat du test de primalité
	printf(GRN "#\x1B[%dC#\n" RESET,w.ws_col-2);
	sprintf(temp,"Prime ?");
	printf(GRN "# " RED "%s" GRN "\x1B[%ldC #\n" RESET,temp,offset2 - strlen(temp));
	
	sprintf(temp,"%s",b?"Yes":"No");
	printf(GRN "#  "RESET"%s\x1B[%ldC"GRN"  #\n" RESET,temp,offset - strlen(temp));
	
	double proba = 1 - ldexp(1,-k);
	
	//affiche la probabilité que la réponse soit correcte
	printf(GRN "#\x1B[%dC#\n" RESET,w.ws_col-2);
	sprintf(temp,"Probability :");
	printf(GRN "# " RED "%s" GRN "\x1B[%ldC #\n" RESET,temp,offset2 - strlen(temp));
	
	sprintf(temp,"%.25lf",b?proba:1);
	printf(GRN "#  "RESET"%s\x1B[%ldC"GRN"  #\n" RESET,temp,offset - strlen(temp));
	
			
	printf(GRN "#\x1B[%dC#\n" RESET,w.ws_col-2);
	for(i=0;i<w.ws_col;i++)
		printf(GRN "#" RESET);
	printf("\n");
}

void Chargement()
{
	
}
