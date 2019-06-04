
#include "graph.h"

void init_graph(matrix *mat) {
    char buf[BUFSIZ] = {0};
    char *rptr = buf;
    char *eptr = NULL;
    const int NUMBASE = 10;

    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    long is_directed = strtol(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);

    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    mat->row = mat->col = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);

    if (mat->col >= 0 && mat->row >= 0) {
        mat_alloc(mat);
    }

    if (is_directed == 1) {
        for (long long i = 0;
             i < mat->col * mat->row && fgets(buf, BUFSIZ, stdin); ++i) {
            rptr = buf;
            long long r = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
            long long c = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
            if (r < mat->row && c < mat->row) {
                mat->mat[r][c] = 1;
            }
        }
    } else if (is_directed == 0) {
        for (long long i = 0;
             i < mat->col * mat->row && fgets(buf, BUFSIZ, stdin); ++i) {
            rptr = buf;
            long long r = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
            long long c = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
            if (r < mat->row && c < mat->row) {
                mat->mat[r][c] = 1;
                mat->mat[c][r] = 1;
            }
        }
    }
}
