all: clear TestPrimalité
	

run: all
	./TestPrimalité
	

TestPrimalité: Exponentiation.o Jacobi.o LectureFichier.o Affichage.o TestPrimalité.o
	gcc -o TestPrimalité Exponentiation.o Jacobi.o LectureFichier.o Affichage.o TestPrimalité.o -Wall -lgmp
	

TestPrimalité.o: TestPrimalité.c TestPrimalité.h Exponentiation.c Exponentiation.h Jacobi.c Jacobi.h LectureFichier.c LectureFichier.h Options.c Affichage.c Affichage.h
	gcc -c -o TestPrimalité.o TestPrimalité.c -Wall -lgmp
	

Exponentiation.o: Exponentiation.c Exponentiation.h
	gcc -c -o Exponentiation.o Exponentiation.c -Wall -lgmp
	

Jacobi.o: Jacobi.c Jacobi.h
	gcc -c -o Jacobi.o Jacobi.c -Wall -lgmp
	

LectureFichier.o: LectureFichier.c LectureFichier.h
	gcc -c -o LectureFichier.o LectureFichier.c -Wall -lgmp
	

Options.o: Options.c
	gcc -c -o Options.o Options.c -Wall
	

Affichage.o: Affichage.c Affichage.h
	gcc -c -o Affichage.o Affichage.c -Wall -lgmp
	

clear:
	clear
	

clean:
	rm -f *.o
	rm -f TestPrimalité
	
