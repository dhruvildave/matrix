
// dhruvil
// Mon 27 May 2019 10:49:37 PM IST
// matrix.c

#include "matrix.h"
#include "pch.h"

// Matrix constructor
void mat_ctor(matrix *mat) {
    mat->col = mat->row = -1;

    mat->mat = NULL;
}

// Matrix destructor
void mat_dtor(matrix *mat) {
    if (mat->col >= 0 && mat->row >= 0) {
        mat->col = mat->row = -1;
        free(mat->mat);
    }
}

// Matrix allocator
void mat_alloc(matrix *mat) {
    mat->mat = (long double **)calloc(mat->row, sizeof(long double *));
    for (long long i = 0; i < mat->row; ++i) {
        mat->mat[i] = (long double *)calloc(mat->col, sizeof(long double));
    }
}

// Matrix initializer
void mat_init(matrix *mat, const int NUMBASE) {
    char buf[BUFSIZ] = {0};
    char *rptr = buf;
    char *eptr = NULL;

    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    mat->row = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
    mat->col = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);

    if (mat->col >= 0 && mat->row >= 0) {
        mat_alloc(mat);
    }

    for (long long i = 0; i < mat->row; ++i) {
        fgets(buf, BUFSIZ, stdin);
        rptr = buf;
        for (long long j = 0; j < mat->col; ++j) {
            mat->mat[i][j] =
                strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
        }
    }
}

// Matrix copy
void mat_cp(matrix *mat_from, matrix *mat_to) {
    mat_to->row = mat_from->row;
    mat_to->col = mat_from->col;

    mat_alloc(mat_to);

    for (long long i = 0; i < mat_from->row; ++i) {
        for (long long j = 0; j < mat_from->col; ++j) {
            mat_to->mat[i][j] = mat_from->mat[i][j];
        }
    }
}

// Matrix move
void mat_mv(matrix *mat_from, matrix *mat_to) {
    mat_cp(mat_from, mat_to);
    mat_dtor(mat_from);
}

// Matrix print
void print(matrix *mat) {
    for (long long i = 0; i < mat->row; ++i) {
        for (long long j = 0; j < mat->col; ++j) {
            (j < mat->col - 1) ? printf("\t%Lf", mat->mat[i][j])
                               : printf("\t%Lf\n", mat->mat[i][j]);
        }
    }
}
