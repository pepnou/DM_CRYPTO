#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#include "LectureFichier.h"

//Ouvre le fichier indiqué par le chemin 'path', trouve le 'indice'-ieme nombre, le lis en base 'base' et le stocke dans 'res'
void Lecture(char* path, int indice, int base, mpz_t res)
{
	FILE* fichier = fopen(path,"r");
	if(!fichier)
	{
		printf("%s  n'est pas un chemin valide\n",path);
		exit(-1);
	}
		
	int i, tmp;
	for(i=1;i<=indice;i++)
	{
		//gmp_fscanf(fichier,"%Zd",res);
		
		tmp = mpz_inp_str(res,fichier,base);
	}
	
	if(tmp == 0)
	{
		printf("\nle nombre à tester n est pas valide dans la base spécifiée\n");
		exit(-1);
	}
	fclose(fichier);
}
