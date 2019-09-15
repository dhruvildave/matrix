
#include "matrix.h"

// drop col num
static matrix *drop_col(matrix *mat, long num) {
    assert(num < mat->col);
    matrix *new = zeros(mat->row, mat->col - 1);
    for (long i = 0; i < mat->row; i++) {
        for (long j = 0, k = 0; j < mat->col; j++) {
            if (j == num) {
                continue;
            }

            new->data[i][k] = mat->data[i][j];
            k++;
        }
    }

    mat_del(mat);
    return new;
}

static matrix *drop_zero_rows(matrix *mat) {
    long arr[mat->row];
    long num = 0;
    for (long i = 0; i < mat->row; ++i) {
        arr[i] = -1;
    }

    for (long i = 0; i < mat->row; ++i) {
        if (is_zero_row(mat, i)) {
            arr[num] = i;
            num++;
        }
    }

    matrix *new = zeros(mat->row - num, mat->col);
    for (long i = 0, k = 0, h = 0; i < mat->row; ++i) {
        if (i == arr[h]) {
            h++;
            continue;
        }

        for (long j = 0; j < mat->col; ++j) {
            new->data[k][j] = mat->data[i][j];
        }

        k++;
    }

    mat_del(mat);
    return new;
}

static void copy_rows(matrix *to, long to_num, matrix *from, long from_num) {
    assert(to_num >= 0 && to_num < to->row);
    assert(from_num >= 0 && from_num < from->row);
    assert(to->col == from->col);
    for (long i = 0; i < to->col; i++) {
        to->data[to_num][i] = from->data[from_num][i];
    }
}

matrix *nullspace(aug_mat *mat, long num_aug_col) {
    matrix *F = mat_cp(mat->rref);
    for (long i = 0; i < num_aug_col; ++i) {
        F = drop_col(F, F->col - 1);
    }

    F = drop_zero_rows(F);
    for (long i = mat->piv->num_pivots - 1; i >= 0; --i) {
        F = drop_col(F, mat->piv->pivot_arr[i]);
    }

    if (F->col == 0) {
        mat_del(F);
        F = zeros(0, 0);
        return F;
    }

    for (long i = 0; i < F->row; ++i) {
        row_scalar_mul(F, i, -1);
    }

    matrix *null_mat = zeros(mat->rref->col - num_aug_col, F->col);
    matrix *I = eye(mat->rref->col - num_aug_col - F->row, F->col);
    long trav[null_mat->row];
    for (long i = 0; i < null_mat->row; ++i) {
        trav[i] = 0;
    }

    for (long i = 0; i < mat->piv->num_pivots; i++) {
        copy_rows(null_mat, mat->piv->pivot_arr[i], F, i);
        trav[mat->piv->pivot_arr[i]] = 1;
    }

    for (long i = 0, j = 0; i < null_mat->row; i++) {
        if (trav[i] == 0) {
            copy_rows(null_mat, i, I, j);
            j++;
        }
    }

    mat_del(F);
    mat_del(I);

    return null_mat;
}
