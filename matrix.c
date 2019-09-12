
// dhruvil
// Mon 27 May 2019 10:49:37 PM IST
// matrix.c

#include "matrix.h"
#include <math.h>

// Matrix constructor
static void mat_ctor(matrix *mat) {
    mat->row = 0;
    mat->col = 0;
    mat->row_major = true;
    mat->data = NULL;
}

// Matrix destructor
static void mat_dtor(matrix *mat) {
    if (mat->row_major) {
        for (long i = 0; i < mat->row; ++i) {
            free(mat->data[i]);
            mat->data[i] = NULL;
        }
    } else {
        for (long i = 0; i < mat->col; ++i) {
            free(mat->data[i]);
            mat->data[i] = NULL;
        }
    }

    free(mat->data);
    mat->col = mat->row = 0;
    mat->data = NULL;
}

// Constructor Wrapper
matrix *mat_init(void) {
    matrix *mat = calloc(1, sizeof(matrix));
    mat_ctor(mat);

    return mat;
}

// Destructor Wrapper
void mat_del(matrix *mat) {
    assert(mat);
    mat_dtor(mat);
    free(mat);
    mat = NULL;
}

// Matrix allocator
void mat_alloc(matrix *mat) {
    if (mat->row >= 0 && mat->col >= 0) {
        mat->data = calloc(mat->row, sizeof(long double *));
        for (long i = 0; i < mat->row; ++i) {
            mat->data[i] = calloc(mat->col, sizeof(long double));
        }
    }
}

// Transpose the matrix
void transpose(matrix *mat) {
    mat->row_major = !(mat->row_major);
    long temp = mat->row;
    mat->row = mat->col;
    mat->col = temp;
}

// Checks if all the values are integers or floats
static bool is_integer_matrix(matrix *mat) {
    if (mat->row_major) {
        for (long i = 0; i < mat->row; ++i) {
            for (long j = 0; j < mat->col; ++j) {
                if (mat->data[i][j] - floorl(mat->data[i][j]) != 0) {
                    return false;
                }
            }
        }
    } else {
        for (long i = 0; i < mat->row; ++i) {
            for (long j = 0; j < mat->col; ++j) {
                if (mat->data[j][i] - floorl(mat->data[j][i]) != 0) {
                    return false;
                }
            }
        }
    }

    return true;
}

// Matrix print
void mat_print(matrix *mat) {
    // printf("\n");
    if (mat->row_major) {
        // printf("\n");
        if (is_integer_matrix(mat)) {
            for (long i = 0; i < mat->row; ++i) {
                for (long j = 0; j < mat->col; ++j) {
                    printf("\t%.0Lf", mat->data[i][j]);
                }
                printf("\n");
            }
            return;
        }

        for (long i = 0; i < mat->row; ++i) {
            for (long j = 0; j < mat->col; ++j) {
                printf("\t%Lf", mat->data[i][j]);
            }
            printf("\n");
        }
    } else {
        // printf("\n");
        if (is_integer_matrix(mat)) {
            for (long i = 0; i < mat->row; ++i) {
                for (long j = 0; j < mat->col; ++j) {
                    printf("\t%.0Lf", mat->data[j][i]);
                }
                printf("\n");
            }
            return;
        }

        for (long i = 0; i < mat->row; ++i) {
            for (long j = 0; j < mat->col; ++j) {
                printf("\t%Lf", mat->data[j][i]);
            }
            printf("\n");
        }
    }
}

// Swap the rows
void swap_rows(matrix *mat, long row1, long row2) {
    assert(row1 >= 0 && row1 < mat->row && row2 >= 0 && row2 < mat->row);
    long double *temp = mat->data[row1];
    mat->data[row1] = mat->data[row2];
    mat->data[row2] = temp;
}

// Swap the columns
void swap_cols(matrix *mat, long col1, long col2) {
    assert(col1 >= 0 && col1 < mat->col && col2 >= 0 && col2 < mat->col);
    long double temp[mat->row];
    for (long i = 0; i < mat->row; ++i) {
        temp[i] = mat->data[i][col1];
    }

    for (long i = 0; i < mat->row; ++i) {
        mat->data[i][col1] = mat->data[i][col2];
    }

    for (long i = 0; i < mat->row; ++i) {
        mat->data[i][col2] = temp[i];
    }
}

// Clean the current memory and user input new matrix
void mat_input(matrix *mat) {
    mat_dtor(mat);
    mat_ctor(mat);

    char buf[BUFSIZ] = {0};
    char *rptr = NULL;
    char *eptr = NULL;
    const int NUMBASE = 10;

    printf("Enter row and column of A seperated by space: ");
    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    mat->row = strtol(__strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
    mat->col = strtol(__strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);

    mat_alloc(mat);

    // printf("Enter %ld rows and %ld columns:\n", mat->row, mat->col);
    for (long i = 0; i < mat->row; ++i) {
        fgets(buf, BUFSIZ, stdin);
        rptr = buf;
        for (long j = 0; j < mat->col; ++j) {
            mat->data[i][j] = strtold(__strtok_r(rptr, " ", &rptr), &eptr);
        }
    }
}

// Return an identity matrix
matrix *eye(long row, long col) {
    assert(row > 0 && col > 0);
    matrix *m = mat_init();
    m->row = row;
    m->col = col;
    mat_alloc(m);

    long dim = 0;
    if (m->row <= m->col) {
        dim = m->row;
    } else {
        dim = m->col;
    }

    for (long i = 0; i < dim; ++i) {
        m->data[i][i] = 1;
    }

    return m;
}

// Return a matrix of zeros
matrix *zeros(long row, long col) {
    assert(row > 0 && col > 0);
    matrix *mat = mat_init();
    mat->row = row;
    mat->col = col;
    mat_alloc(mat);
    return mat;
}

// Return a matrix of ones
matrix *ones(long row, long col) {
    assert(row > 0 && col > 0);
    matrix *mat = mat_init();
    mat->row = row;
    mat->col = col;
    mat_alloc(mat);
    for (long i = 0; i < mat->row; ++i) {
        for (long j = 0; j < mat->col; ++j) {
            mat->data[i][j] = 1;
        }
    }

    return mat;
}

void row_scalar_mul(long double *row, long len, long double num) {
    for (long i = 0; i < len; ++i) {
        row[i] *= num;
    }
}

// row2 - row1
void sub_row(matrix *A, long row1, long row2, matrix *I) {
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
