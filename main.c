
// dhruvil
// Mon 27 May 2019 02:07:07 PM IST
// main.c

#include "graph.h"

int main(void) {
    char buf[BUFSIZ] = {0};
    char *rptr = buf;
    char *eptr = NULL;
    const int NUMBASE = 10;

    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    long test = strtol(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
    for (long i = 0; i < test; ++i) {
        matrix graph;
        mat_ctor(&graph);
        mat_init(&graph);

        printf("%Lf\n", det(&graph));
        print(&graph);
        mat_dtor(&graph);
    }

    return 0;
}
