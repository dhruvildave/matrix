
// dhruvil
// regression.c
// Tue 05 Nov 2019 10:31:48 PM IST

#include "matrix.h"

static matrix *mat_mul(matrix *A, matrix *B) {
    assert(A->col == B->row);
    matrix *ans = zeros(A->row, B->col);
    for (long i = 0; i < A->row; ++i) {
        for (long j = 0; j < B->col; ++j) {
            for (long k = 0; k < A->col; ++k) {
                ans->data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }

    return ans;
}

static matrix *mat_inv(matrix *mat) {
    matrix *I = eye(mat->row, mat->col);
    aug_mat *x = solve(mat, I);

    matrix *inv = zeros(mat->row, mat->col);
    for (long i = 0; i < I->row; ++i) {
        for (long j = 0; j < I->col; ++j) {
            inv->data[i][j] = x->rref->data[i][j + mat->col];
        }
    }

    aug_del(x);
    mat_del(I);

    return inv;
}

matrix *lin_reg(matrix *mat) {
    matrix *A = zeros(mat->row, (mat->col - 1) * 2 + 1);
    matrix *b = zeros(mat->row, 1);

    for (long i = 0, j = mat->col - 1; i < mat->row; ++i) {
        A->data[i][0] = 1;
        b->data[i][0] = mat->data[i][j];
    }

    for (long i = 0; i < mat->row; ++i) {
        for (long j = 0; j < mat->col - 1; ++j) {
            A->data[i][j + 1] = mat->data[i][j];
        }
    }

    for (long i = 0; i < mat->row; ++i) {
        for (long j = 0; j < mat->col; ++j) {
            A->data[i][mat->col + j] = mat->data[i][j] * mat->data[i][j];
        }
    }

    matrix *At = transpose(A);
    matrix *mul = mat_mul(At, A);
    matrix *inv = mat_inv(mul);

    mat_del(mul);

    matrix *mulAt = mat_mul(inv, At);
    mat_del(inv);

    matrix *final = mat_mul(mulAt, b);

    mat_del(A);
    mat_del(b);
    mat_del(At);

    mat_del(mulAt);

    return final;
}
