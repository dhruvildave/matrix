
#include "matrix.h"

// Multiply a row by a scalar
static void row_scalar_mul(long double *row, long len, long double num) {
    for (long i = 0; i < len; ++i) {
        if (row[i] != 0) {
            row[i] *= num;
        }
    }
}

static bool is_zero_row(long double *row, long len) {
    for (long i = 0; i < len; ++i) {
        if (row[i] != 0) {
            return false;
        }
    }

    return true;
}

// row2 - row1
static void sub_row(matrix *A, long row1, long row2) {
    long double mul = A->data[row2][row1] / A->data[row1][row1];
    long double arr[A->col];
    // long double arrI[I->col];
    for (long i = 0; i < A->col; ++i) {
        arr[i] = A->data[row1][i] * mul;
    }

    // for (long i = 0; i < I->col; ++i) {
    //     arrI[i] = I->data[row1][i] * mul;
    // }

    for (long i = 0; i < A->col; ++i) {
        A->data[row2][i] -= arr[i];
    }

    // for (long i = 0; i < I->col; ++i) {
    //     I->data[row2][i] -= arrI[i];
    // }
}

// Reduced Row Echelon Form
void rref(matrix *A) {
    // Doing row swap if pivot is 0
    // long num_pivot = 0;
    // long pivot_arr[A->col + 1];
    // for (long i = 0; i < A->col + 1; ++i) {
    //     pivot_arr[i] = -1;
    // }
    bool trace = false;

    long k = 0;
    // bool check_piv = false;
    long dim = (A->row < A->col) ? A->row : A->col;
    for (long i = 0; i < dim; ++i) {
        if (A->data[i][i] == 0) {
            for (k = i + 1; k < A->row; ++k) {
                if (A->data[k][i] != 0) {
                    break;
                }
            }

            if (k == A->row) {
                k = i + 1;
                // check_piv = true;
                break;
            }

            swap_rows(A, k, i);
        }

        // pivot_arr[num_pivot] = i;
        // num_pivot++;

        for (long j = i + 1; j < A->row; ++j) {
            if (A->data[j][i] != 0) {
                sub_row(A, i, j);
            }

            if (trace) {
                mat_print(A);
                printf("\n");
                // mat_print(I);
                // printf("\n");
            }
        }
    }

    // if (check_piv) {
    //     for (; k < A->row; ++k) {
    //         for (long i = k; i < A->row; ++i) {
    //             if (A->data[i][k] != 0) {
    //                 pivot_arr[num_pivot] = k;
    //                 num_pivot++;
    //             }
    //         }
    //     }
    // }

    for (long i = dim - 1; i > 0; --i) {
        for (long j = i - 1; j >= 0; --j) {
            if (A->data[j][i] != 0 && A->data[i][i] != 0) {
                sub_row(A, i, j);
            }

            if (trace) {
                mat_print(A);
                printf("\n");
                // mat_print(I);
                // printf("\n");
            }
        }
    }

    // printf("%ld\n", num_pivot);
    // for (long i = 0; pivot_arr[i] != -1; ++i) {
    //     printf("\t%ld", pivot_arr[i]);
    // }
    // printf("\n\n");

    // long dim = (A->row < A->col) ? A->row : A->col;
    for (long i = 0; i < dim; ++i) {
        if (A->data[i][i] != 0) {
            // row_scalar_mul(I->data[i], I->col, 1 / A->data[i][i]);
            row_scalar_mul(A->data[i], A->col, 1 / A->data[i][i]);
        }
    }

    mat_print(A);
    printf("\n");
    // mat_print(I);

    // mat_del(I);
}
