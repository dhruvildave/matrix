
#include "matrix.h"

// Multiply a row by a scalar
void row_scalar_mul(matrix *mat, long num, long double mul) {
    for (long i = 0; i < mat->col; ++i) {
        mat->data[num][i] *= mul;
    }
}

bool is_zero_row(matrix *mat, long num) {
    assert(num >= 0 && num < mat->row);
    for (long i = 0; i < mat->col; ++i) {
        if (mat->data[num][i] != 0) {
            return false;
        }
    }

    return true;
}

bool is_zero_col(matrix *mat, long num) {
    assert(num < mat->col && num >= 0);
    for (long i = 0; i < mat->row; ++i) {
        if (mat->data[i][num] != 0) {
            return false;
        }
    }

    return true;
}

// row2 - row1
static void sub_row_rref(matrix *A, long row1, long row2) {
    long double mul = A->data[row2][row1] / A->data[row1][row1];
    long double arr[A->col];

    for (long i = 0; i < A->col; ++i) {
        arr[i] = A->data[row1][i] * mul;
    }

    for (long i = 0; i < A->col; ++i) {
        A->data[row2][i] -= arr[i];
    }
}

// row2 - row1 simultaneously in A and b
static void sub_row_Ab(matrix *A, long row1, long row2, matrix *b) {
    long double mul = A->data[row2][row1] / A->data[row1][row1];
    long double arr[A->col];
    long double arr_b[b->col];

    for (long i = 0; i < A->col; ++i) {
        arr[i] = A->data[row1][i] * mul;
    }

    for (long i = 0; i < b->col; ++i) {
        arr_b[i] = b->data[row1][i] * mul;
    }

    for (long i = 0; i < A->col; ++i) {
        A->data[row2][i] -= arr[i];
    }

    for (long i = 0; i < b->col; ++i) {
        b->data[row2][i] -= arr_b[i];
    }
}

static void sub_row_piv_rref(matrix *A, long row1, long row2, long piv) {
    long double mul = A->data[row2][piv] / A->data[row1][piv];
    long double arr[A->col];

    for (long i = 0; i < A->col; ++i) {
        arr[i] = A->data[row1][i] * mul;
    }

    for (long i = 0; i < A->col; ++i) {
        A->data[row2][i] -= arr[i];
    }
}

static void sub_row_piv_Ab(matrix *A, long row1, long row2, long piv,
                           matrix *b) {
    long double mul = A->data[row2][piv] / A->data[row1][piv];
    long double arr[A->col];
    long double arr_b[b->col];

    for (long i = 0; i < A->col; ++i) {
        arr[i] = A->data[row1][i] * mul;
    }

    for (long i = 0; i < b->col; ++i) {
        arr_b[i] = b->data[row1][i] * mul;
    }

    for (long i = 0; i < A->col; ++i) {
        A->data[row2][i] -= arr[i];
    }

    for (long i = 0; i < b->col; ++i) {
        b->data[row2][i] -= arr_b[i];
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
                sub_row_rref(A, i, k);
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
            sub_row_piv_rref(new, i, j, curr_piv_col);
        }

        for (long j = i + 1; j < new->row; ++j) {
            sub_row_piv_rref(new, i, j, curr_piv_col);
        }
    }

    return new;
}

// A * x = b
aug_mat *solve(matrix *A, matrix *b) {
    // Doing row swap if pivot is 0
    bool trace = false;
    long num_pivot = 0;
    long piv_arr[A->col];

    for (long i = 0; i < A->col; ++i) {
        piv_arr[i] = -1;
    }

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
            swap_rows(b, k, i);
        }

        // At this point it is guaranteed that pivot is non-zero
        // So we elemination matrix to make the pivot 1
        row_scalar_mul(b, i, 1 / A->data[i][j]);
        row_scalar_mul(A, i, 1 / A->data[i][j]);

        for (long k = i + 1; k < A->row; ++k) {
            if (A->data[k][j] != 0) {
                sub_row_Ab(A, i, k, b);
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

    matrix *new_A = zeros(A->row, A->col);
    matrix *new_b = zeros(b->row, b->col);
    {
        long i = 0;
        for (i = 0; non_zero_row[i] != -1; ++i) {
            // copy the row
            for (long j = 0; j < A->col; ++j) {
                new_A->data[i][j] = A->data[non_zero_row[i]][j];
            }

            for (long j = 0; j < b->col; ++j) {
                new_b->data[i][j] = b->data[non_zero_row[i]][j];
            }
        }

        for (; zero_row[i] != -1; ++i) {
            // copy the row
            for (long j = 0; j < A->col; ++j) {
                new_A->data[i][j] = A->data[zero_row[i]][j];
            }

            for (long j = 0; j < b->col; ++j) {
                new_b->data[i][j] = b->data[zero_row[i]][j];
            }
        }
    }

    //
    // <<< Rearranging the zero rows in the elemination matrix

    // Continuing elemination for rref
    long curr_piv_row = -1;
    long curr_piv_col = -1;
    for (long i = 0; i < new_A->row; ++i) {
        if (is_zero_row(new_A, i)) {
            break;
        }

        for (long j = 0; j < new_A->col; ++j) {
            if (new_A->data[i][j] != 0) {
                if (i > curr_piv_row && j > curr_piv_col) {
                    curr_piv_row = i;
                    curr_piv_col = j;
                }
            }
        }

        piv_arr[num_pivot++] = curr_piv_col;

        if (A->data[curr_piv_row][curr_piv_col] != 1) {
            row_scalar_mul(new_b, i,
                           1 / new_A->data[curr_piv_row][curr_piv_col]);
            row_scalar_mul(new_A, i,
                           1 / new_A->data[curr_piv_row][curr_piv_col]);
        }

        for (long j = 0; j < i; ++j) {
            sub_row_piv_Ab(new_A, i, j, curr_piv_col, new_b);
        }

        for (long j = i + 1; j < new_A->row; ++j) {
            sub_row_piv_Ab(new_A, i, j, curr_piv_col, new_b);
        }
    }

    pivot_data *piv = calloc(1, sizeof(pivot_data));
    piv->num_pivots = num_pivot;
    piv->pivot_arr = calloc(num_pivot, sizeof(long));
    for (long i = 0; i < num_pivot; ++i) {
        piv->pivot_arr[i] = piv_arr[i];
    }

    aug_mat *new = calloc(1, sizeof(aug_mat));
    new->rref = aug(new_A, new_b);
    new->piv = piv;

    for (long i = 0; i < piv->num_pivots; ++i) {
        printf("\t%ld", piv->pivot_arr[i]);
    }
    printf("\n");

    mat_del(new_A);
    mat_del(new_b);

    return new;
}
