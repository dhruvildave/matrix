
#include "matrix.h"
#include "util.h"

// row2 - row1 with pivot element as multiplier
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

// checks if zero solution has zero rows
static bool is_consistent(aug_mat *mat) {
    long double rowindex[mat->rref->row];
    for (long i = 0; i < mat->rref->row; ++i) {
        rowindex[i] = 0;
    }

    for (long i = 0; i < mat->piv->num_pivots; i++) {
        rowindex[mat->piv->pivot_arr[i]] = 1;
    }

    for (long i = 0; i < mat->rref->row; i++) {
        if (rowindex[i] != 1) {
            if (is_zero_row(mat->rref, i)) {
                return false;
            }
        }
    }

    return true;
}

// Solve A * x = b
aug_mat *solve(matrix *A, matrix *b) {
    assert(A->row == b->row);
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

            // Break the elimination if no non-zero pivot exists
            if (k == A->row) {
                break;
            }

            swap_rows(A, k, i);
            swap_rows(b, k, i);
        }

        if (trace) {
            mat_print(A);
            printf("\n");
        }

        // At this point it is guaranteed that pivot is non-zero
        // So we elimination matrix to make the pivot 1
        row_scalar_mul(b, i, 1 / A->data[i][j]);
        row_scalar_mul(A, i, 1 / A->data[i][j]);

        if (trace) {
            mat_print(A);
            printf("\n");
        }

        for (long k = i + 1; k < A->row; ++k) {
            if (A->data[k][j] != 0) {
                sub_row_piv_Ab(A, i, k, j, b);
            }

            if (trace) {
                mat_print(A);
                printf("\n");
            }
        }

        i++;
        j++;
    }

    // At this point we are done with forward elimination

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

    // Continuing elimination for rref
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

    // Storing the pivots
    pivot_data *piv = calloc(1, sizeof(pivot_data));
    piv->num_pivots = num_pivot;
    piv->pivot_arr = calloc(num_pivot, sizeof(long));
    for (long i = 0; i < num_pivot; ++i) {
        piv->pivot_arr[i] = piv_arr[i];
    }

    aug_mat *new = calloc(1, sizeof(aug_mat));
    new->rref = aug(new_A, new_b);
    new->piv = piv;

    // printf("The pivots are:\n");
    // for (long i = 0; i < piv->num_pivots; ++i) {
    //     printf("\t%ld", piv->pivot_arr[i]);
    // }
    // printf("\n\n");

    mat_del(new_A);
    mat_del(new_b);

    return new;
}

// Checks and returns the solution set
void solution(aug_mat *mat, matrix *nullmat) {
    long double sol[mat->rref->col - 1];
    for (long i = 0; i < mat->rref->col - 1; ++i) {
        sol[i] = 0;
    }

    for (long i = 0; i < mat->piv->num_pivots; i++) {
        long zerocolcount = 0;
        for (long k = 0; k < mat->piv->pivot_arr[i]; k++) {
            if (is_zero_col(mat->rref, k)) {
                zerocolcount++;
            }
        }

        if (mat->piv->pivot_arr[i] - zerocolcount < mat->rref->row) {
            sol[mat->piv->pivot_arr[i]] =
                mat->rref->data[mat->piv->pivot_arr[i] - zerocolcount]
                               [mat->rref->col - 1];
        }
    }

    printf("\n\nNullspace of the equation is:\n");
    mat_print(nullmat);
    if (nullmat->row == 0 && nullmat->col == 0) {
        printf("Only zero vector as a nullspace\n");
    }

    long rank = mat->piv->num_pivots;
    if (rank == mat->rref->row && rank == mat->rref->col - 1) {
        printf("\nAx = b has a unique solution\n");
        printf("Particular solution of the equation is:\n");
        for (long i = 0; i < mat->rref->col - 1; i++) {
            printf("x%ld == %.2Lf\n", i, sol[i]);
        }

        return;
    }

    if (rank == mat->rref->row) {
        printf("\nAx = b has infinitely many solutions\n");
        for (long i = 0; i < mat->rref->col - 1; i++) {
            printf("x%ld == %.2Lf\n", i, sol[i]);
        }

        return;
    }

    if (rank == mat->rref->col - 1) {
        if (is_consistent(mat)) {
            printf("\nAx = b has a unique solution\n");
            for (long i = 0; i < mat->rref->col - 1; i++) {
                printf("x%ld == %.2Lf\n", i, sol[i]);
            }
        } else {
            printf("\nAx = b has no solution\n");
        }

        return;
    }

    if (is_consistent(mat)) {
        printf("\nAx = b has infinitely many solutions\n");
        for (long i = 0; i < mat->rref->col - 1; i++) {
            printf("x%ld == %.2Lf\n", i, sol[i]);
        }

        return;
    }

    printf("\nAx = b has No Solution\n");
}
