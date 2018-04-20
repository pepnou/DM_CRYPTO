#include "Exponentiation.h"
#include "Jacobi.h"
#include "LectureFichier.h"
#include "Options.c"

bool SolovayStrassen(mpz_t n,int k);
void AfficherRes(bool b, mpz_t n, int k, int base, bool v);
