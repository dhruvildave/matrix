
// dhruvil
// Mon 27 May 2019 02:07:07 PM IST
// main.c

#include "matrix.h"
#include "util.h"

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

    aug_mat *x = solve(A, b);
    mat_print_aug(x->rref, A->col);
    printf("\n");

    matrix *p = nullspace(x, b->col);
    mat_print(p);

    solution(x, p);

    mat_del(A);
    mat_del(b);
    aug_del(x);
    mat_del(p);
    return 0;
}
