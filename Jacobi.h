#define debug printf("line : %d in function : %s\n",__LINE__,__func__);


int Jacobi(mpz_t a, mpz_t n);
bool Prime(mpz_t a, mpz_t b);
void Euclide(mpz_t a, mpz_t b, mpz_t res);
