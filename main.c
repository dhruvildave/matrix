
// dhruvil
// Mon 27 May 2019 02:07:07 PM IST
// main.c

#include "graph.h"

int main(void) {
    char buf[BUFSIZ] = {0};
    char *rptr = buf;
    char *eptr = NULL;
    const int NUMBASE = 10;

    printf("Enter the number of testcases: ");
    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    long test = strtol(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
    printf("\n");
    for (long i = 0; i < test; ++i) {
        // graph g;
        // graph_ctor(&g);
        // graph_init(&g);

        // graph_pprint(&g);

        // graph_dtor(&g);

        matrix a;
        mat_ctor(&a);
        mat_init(&a);

        matrix b;
        mat_ctor(&b);
        // mat_inv(&a, &b);

        matrix c;
        mat_ctor(&c);
        // mat_inv(&b, &a);

        mat_pprint(&a);

        mat_dtor(&a);
        mat_dtor(&b);
        mat_dtor(&c);
        mat_dtor(&a);
    }

    return 0;
}
