
// dhruvil
// Mon 27 May 2019 02:07:07 PM IST
// main.c

#include "graph.h"

int main(void) {
    char buf[BUFSIZ] = {0};
    char *rptr = buf;
    char *eptr = NULL;
    const int NUMBASE = 10;

    // printf("Enter the number of testcases: ");
    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    long test = strtol(__strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
    // printf("\n");
    for (long i = 0; i < test; ++i) {
        // graph *g = New(&Graph);
        // graph_init(g);
        // graph_pprint(g);
        // Delete(g);

        matrix *a = New(&Matrix);

        mat_init(a);
        transpose(a);

        // matrix *b = New(&Matrix);
        // mat_inv(a, b);

        // matrix_multiply(a, b);
        mat_print(a);

        Delete(a);
        // Delete(b);
    }

    return 0;
}
