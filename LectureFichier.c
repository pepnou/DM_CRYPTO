#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#include "LectureFichier.h"


void Lecture(char* path, int indice, int base, mpz_t res)
{
	FILE* fichier = fopen(path,"r");
	if(!fichier)
	{
		printf("%s  n'est pas un chemin valide\n",path);
		exit(-1);
	}
	
	int i;
	for(i=1;i<=indice;i++)
	{
		//gmp_fscanf(fichier,"%Zd",res);
		
		if(mpz_inp_str(res,fichier,base) == 0)
		{
			printf("le nombre à tester n est pas valide dans la base spécifiée\n");
			exit(-1);
		}
	}
}
