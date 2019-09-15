
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

    printf("::DISCLAIMER::\n");
    printf("THIS SOFTWARE HAS BEEN HEAVILY TESTED FOR VARIOUS TEST CASES OF "
           "VARIOUS DIMENSIONS\nPLEASE MAKE SURE TO ENTER THE DIMENSIONS "
           "CORRECTLY AND LEAVE NO DIMENSION OF ENTRY UNFILLED\nIT MAY LEAD TO "
           "UNDEFINED BEHAVIOR\n");

    matrix *A = mat_init();
    printf("\n\nEnter A:\n");
    printf("a(11) a(12) ... a(1n)\n");
    printf(".....................\n");
    printf("a(n1) a(n2) ... a(nn)\n");
    mat_input(A);

    matrix *b = mat_init();
    printf("\n\nEnter b:\n");
    printf("For solving a system of linear equations,\n");
    printf("Enter the number of columns of b should be 1\n");
    printf("b(11) b(12) ... b(1n)\n");
    printf(".....................\n");
    printf("b(n1) b(n2) ... b(nn)\n");
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
