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
		printf("%s  is not a valid path\n",path);
		exit(-1);
	}
		
	int i, tmp;
	for(i=1;i<=indice;i++)
	{
		tmp = mpz_inp_str(res,fichier,base);
	}
	
	if(tmp == 0)
	{
		printf("\nThe number is not valid in the specified base or the \
		 file does not contain the INDEX-positionned number \n");
		exit(-1);
	}
	fclose(fichier);
}
