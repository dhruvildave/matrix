
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

    matrix *mat = mat_init();
    mat_input(mat);

    matrix *coef = lin_reg(mat);
    mat_print(coef);

    mat_del(coef);
    mat_del(mat);

    return 0;
}
