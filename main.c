
// dhruvil
// Mon 27 May 2019 02:07:07 PM IST
// main.c

#include "matrix.h"

int main(void) {

    matrix *a = mat_init();
    mat_input(a);

    mat_print(a);

    mat_del(a);

    return 0;
}
