
// dhruvil
// Mon 27 May 2019 02:07:07 PM IST
// main.c

#include "matrix.h"

int main(void) {
#if !defined(__linux__)
    printf("Source code compliant only with Linux\n");
    exit(EXIT_FAILURE);

#endif // __linux__

    matrix *A = mat_init();
    printf("Enter A:\n");
    mat_input(A);

    matrix *b = mat_init();
    printf("Enter b:\n");
    mat_input(b);

    matrix *x = solve(A, b);
    mat_print_aug(x, A->col);

    // matrix *x = rref(A);

    mat_del(A);
    mat_del(b);
    mat_del(x);
    return 0;
}
