
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
        mat->mat = NULL;
    }
}

// Matrix allocator
void mat_alloc(matrix *mat) {
    if (mat->row >= 0 && mat->col >= 0) {
        mat->mat = (long double **)calloc(mat->row, sizeof(long double *));
        for (long long i = 0; i < mat->row; ++i) {
            mat->mat[i] = (long double *)calloc(mat->col, sizeof(long double));
        }
    }
}

// Matrix initializer
void mat_init(matrix *mat) {
    char buf[BUFSIZ] = {0};
    char *rptr = buf;
    char *eptr = NULL;
    const int NUMBASE = 10;

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
            mat->mat[i][j] = strtold(strtok_r(rptr, " ", &rptr), &eptr);
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

// Matrix addition
void add(matrix *addend0, matrix *addend1) {
    if (addend0->row == addend1->row && addend0->col == addend1->col) {
        for (long long i = 0; i < addend0->row; ++i) {
            for (long long j = 0; j < addend0->col; ++j) {
                addend0->mat[i][j] += addend1->mat[i][j];
            }
        }
    }
}

// Matrix substraction
void sub(matrix *subend0, matrix *subend1) {
    if (subend0->row == subend1->row && subend0->col == subend1->col) {
        for (long long i = 0; i < subend0->row; ++i) {
            for (long long j = 0; j < subend0->col; ++j) {
                subend0->mat[i][j] -= subend1->mat[i][j];
            }
        }
    }
}

// Matrix transpose
void transpose(matrix *mat) {
    if (mat->row == mat->col) {
        for (long long i = 0; i < mat->row; ++i) {
            for (long long j = 0; j < i; ++j) {
                long double temp = mat->mat[i][j];
                mat->mat[i][j] = mat->mat[j][i];
                mat->mat[j][i] = temp;
            }
        }
    } else {
        matrix new;
        mat_ctor(&new);
        mat_mv(mat, &new);

        mat->row = new.col;
        mat->col = new.row;

        mat_alloc(mat);

        for (long long i = 0; i < new.row; ++i) {
            for (long long j = 0; j < new.col; ++j) {
                mat->mat[j][i] = new.mat[i][j];
            }
        }

        mat_dtor(&new);
    }
}
