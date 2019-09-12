
// dhruvil
// Mon 27 May 2019 02:07:07 PM IST
// main.c

#include "matrix.h"

int main(void) {
    matrix *mat = mat_init();
    mat_input(mat);
    rref(mat);

    mat_del(mat);
    return 0;
}
