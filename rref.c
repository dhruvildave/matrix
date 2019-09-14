
#include "matrix.h"

// Multiply a row by a scalar
static void row_scalar_mul(matrix *mat, long num, long double mul) {
    for (long i = 0; i < mat->col; ++i) {
        mat->data[num][i] *= mul;
    }
}

static bool is_zero_row(matrix *mat, long num) {
    assert(num >= 0 && num < mat->row);
    for (long i = 0; i < mat->col; ++i) {
        if (mat->data[num][i] != 0) {
            return false;
        }
    }

    return true;
}

static bool is_zero_col(matrix *mat, long num) {
    assert(num < mat->col && num >= 0);
    for (long i = 0; i < mat->row; ++i) {
        if (mat->data[i][num] != 0) {
            return false;
        }
    }

    return true;
}

// row2 - row1
static void sub_row(matrix *A, long row1, long row2) {
    long double mul = A->data[row2][row1] / A->data[row1][row1];
    long double arr[A->col];

    for (long i = 0; i < A->col; ++i) {
        arr[i] = A->data[row1][i] * mul;
    }

    for (long i = 0; i < A->col; ++i) {
        A->data[row2][i] -= arr[i];
    }
}

static void sub_row_piv(matrix *A, long row1, long row2, long piv) {
    long double mul = A->data[row2][piv] / A->data[row1][piv];
    long double arr[A->col];

    for (long i = 0; i < A->col; ++i) {
        arr[i] = A->data[row1][i] * mul;
    }

    for (long i = 0; i < A->col; ++i) {
        A->data[row2][i] -= arr[i];
    }
}

// Reduced Row Echelon Form
matrix *rref(matrix *A) {
    // Doing row swap if pivot is 0

    bool trace = false;

    // long dim = (A->row < A->col) ? A->row : A->col;
    for (long i = 0, j = 0; i < A->row && j < A->col;) {
        while (is_zero_col(A, j)) {
            j++;

            if (j == A->col) {
                break;
            }
        }

        if (j == A->col) {
            break;
        }

        // At this point it is guaranteed that matrix is non-zero
        // Also, we have our first non-zero column

        // Swapping the rows to get a non-zero pivot if it exists
        if (A->data[i][j] == 0) {
            long k = 0;
            for (k = i + 1; k < A->row; ++k) {
                if (A->data[k][j] != 0) {
                    break;
                }
            }

            // Break the elemination if no non-zero pivot exists
            if (k == A->row) {
                break;
            }

            swap_rows(A, k, i);
        }

        // At this point it is guaranteed that pivot is non-zero
        // So we elemination matrix to make the pivot 1
        row_scalar_mul(A, i, 1 / A->data[i][j]);

        for (long k = i + 1; k < A->row; ++k) {
            if (A->data[k][j] != 0) {
                sub_row(A, i, k);
            }

            if (trace) {
                mat_print(A);
                printf("\n");
            }
        }

        i++;
        j++;
    }

    // At this point we are done with forward elemination

    // >>> Rearranging the zero rows in the elemination matrix
    //

    long zero_row[A->row + 1];
    long non_zero_row[A->row + 1];

    for (long i = 0; i < A->row + 1; ++i) {
        zero_row[i] = non_zero_row[i] = -1;
    }

    for (long i = 0, j = 0, k = 0; k < A->row; ++k) {
        if (is_zero_row(A, k)) {
            zero_row[i] = k;
            i++;
        } else {
            non_zero_row[j] = k;
            j++;
        }
    }

    matrix *new = zeros(A->row, A->col);
    {
        long i = 0;
        for (i = 0; non_zero_row[i] != -1; ++i) {
            // copy the row
            for (long j = 0; j < A->col; ++j) {
                new->data[i][j] = A->data[non_zero_row[i]][j];
            }
        }

        for (; zero_row[i] != -1; ++i) {
            // copy the row
            for (long j = 0; j < A->col; ++j) {
                new->data[i][j] = A->data[zero_row[i]][j];
            }
        }
    }

    //
    // <<< Rearranging the zero rows in the elemination matrix

    // Continuing elemination for rref
    long curr_piv_row = -1;
    long curr_piv_col = -1;
    for (long i = 0; i < new->row; ++i) {
        if (is_zero_row(new, i)) {
            break;
        }

        for (long j = 0; j < new->col; ++j) {
            if (new->data[i][j] != 0) {
                if (i > curr_piv_row && j > curr_piv_col) {
                    curr_piv_row = i;
                    curr_piv_col = j;
                }
            }
        }

        if (A->data[curr_piv_row][curr_piv_col] != 1) {
            row_scalar_mul(new, i, 1 / new->data[curr_piv_row][curr_piv_col]);
        }

        for (long j = 0; j < i; ++j) {
            sub_row_piv(new, i, j, curr_piv_col);
        }

        for (long j = i + 1; j < new->row; ++j) {
            sub_row_piv(new, i, j, curr_piv_col);
        }
    }

    mat_del(A);
    return new;
}
