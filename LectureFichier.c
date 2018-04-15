#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#include "LectureFichier.h"


void Lecture(char* path, int indice, mpz_t res)
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
		gmp_fscanf(fichier,"%Zi",res);
	}
}
