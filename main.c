
// dhruvil
// Mon 27 May 2019 02:07:07 PM IST
// main.c

#if !defined(__linux__)
printf("Source code compliant only with Linux");
exit(EXIT_FAILURE);

#endif // __linux__

#include "matrix.h"

int main(void) {
    matrix *mat = mat_init();
    printf("Enter A:\n");
    mat_input(mat);
    rref(mat);

    mat_del(mat);
    return 0;
}
