
#include "matrix.h"

static void row_scalar_mul(long double *row, long len, long double num) {
    for (long i = 0; i < len; ++i) {
        row[i] *= num;
    }
}

// row2 - row1
static void sub_row(matrix *A, long row1, long row2, matrix *I) {
    long double mul = A->data[row2][row1] / A->data[row1][row1];
    long double arr[A->col];
    long double arrI[A->col];
    for (long i = 0; i < A->col; ++i) {
        arr[i] = A->data[row1][i] * mul;
    }

    for (long i = 0; i < I->col; ++i) {
        arrI[i] = I->data[row1][i] * mul;
    }

    for (long i = 0; i < A->col; ++i) {
        A->data[row2][i] -= arr[i];
    }

    for (long i = 0; i < I->col; ++i) {
        I->data[row2][i] -= arrI[i];
    }
}

// Reduced Row Echelon Form
void rref(matrix *A) {
    // Doing row swap if pivot is 0
    long num_pivot = 0;

    matrix *I = mat_init();
    printf("Enter b:\n");
    mat_input(I);
    for (long i = 0; i < A->row - 1; ++i) {
        if (A->data[i][i] == 0) {
            long k = 0;
            for (k = i + 1; k < A->row; ++k) {
                if (A->data[k][i] != 0) {
                    break;
                }
            }

            if (k == A->row) {
                break;
            } else {
                swap_rows(A, k, i);
            }
        }

        num_pivot++;

        for (long j = i + 1; j < A->row; ++j) {
            if (A->data[i][j] != 0) {
                sub_row(A, i, j, I);
            }
        }
    }

    for (long i = A->row - 1; i > 0; --i) {
        for (long j = i - 1; j >= 0; --j) {
            if (A->data[j][i] != 0) {
                sub_row(A, i, j, I);
            }
        }
    }

    if (A->data[A->row - 1][A->col - 1] != 0) {
        num_pivot++;
    }

    printf("%ld\n", num_pivot);

    for (long i = 0; i < A->row; ++i) {
        row_scalar_mul(I->data[i], I->col, 1 / A->data[i][i]);
        row_scalar_mul(A->data[i], A->col, 1 / A->data[i][i]);
    }

    mat_print(A);
    printf("\n");
    mat_print(I);

    mat_del(I);
}
