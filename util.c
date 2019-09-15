
#include "util.h"
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
