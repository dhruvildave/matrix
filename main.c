
// dhruvil
// Mon 27 May 2019 02:07:07 PM IST
// main.c

#include "matrix.h"
#include "pch.h"

int main(void) {
    char buf[BUFSIZ] = {0};
    char *rptr = buf;
    char *eptr = NULL;
    const int NUMBASE = 10;

    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    long test = strtol(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
    for (long i = 0; i < test; ++i) {
        matrix m0;
        mat_ctor(&m0);
        mat_init(&m0, NUMBASE);

        matrix m1;
        mat_ctor(&m1);
        mat_cp(&m0, &m1);
        mat_mv(&m0, &m1);

        // mat_init(&m1, NUMBASE);
        printf("%lld %lld\n", m1.row, m1.col);
        printf("%lld %lld\n", m0.row, m0.col);

        print(&m1);
        print(&m0);

        mat_dtor(&m0);
        mat_dtor(&m1);
    }

    return 0;
}
