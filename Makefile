all: clear TestPrimalité
	

run: all
	./TestPrimalité
	

TestPrimalité: TestPrimalité.o Exponentiation.o Jacobi.o LectureFichier.o
	gcc -o TestPrimalité TestPrimalité.o Exponentiation.o Jacobi.o LectureFichier.o -Wall -lgmp
	

TestPrimalité.o: TestPrimalité.c TestPrimalité.h
	gcc -c -o TestPrimalité.o TestPrimalité.c -Wall -lgmp
	

Exponentiation.o: Exponentiation.c Exponentiation.h
	gcc -c -o Exponentiation.o Exponentiation.c -Wall -lgmp
	

Jacobi.o: Jacobi.c Jacobi.h
	gcc -c -o Jacobi.o Jacobi.c -Wall -lgmp
	

LectureFichier.o: LectureFichier.c LectureFichier.h
	gcc -c -o LectureFichier.o LectureFichier.c -Wall -lgmp
	

clear:
	clear
	

clean:
	rm -f *.o
	rm -f TestPrimalité
	
