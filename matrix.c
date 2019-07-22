
// dhruvil
// Mon 27 May 2019 10:49:37 PM IST
// matrix.c

#include "matrix.h"
#include <math.h>

// Checks the validity of matrix
static bool is_valid_matrix(matrix *mat) {
    if (mat->row > 0 && mat->col > 0 && mat->mat != NULL) {
        return true;
    }

    return false;
}

// Matrix constructor
void mat_ctor(matrix *mat) {
    mat->col = mat->row = -1;

    mat->mat = NULL;
}

// Matrix destructor
void mat_dtor(matrix *mat) {
    if (is_valid_matrix(mat)) {
        for (long long i = 0; i < mat->row; ++i) {
            free(mat->mat[i]);
            mat->mat[i] = NULL;
        }

        free(mat->mat);
        mat->col = mat->row = -1;
        mat->mat = NULL;
    }
}

// Constructor Wrapper
static void *ctor(void *_self) {
    matrix *self = _self;
    assert(self);
    mat_ctor(self);
    return self;
}

// Destructor Wrapper
static void *dtor(void *_self) {
    matrix *self = _self;
    assert(self && self->mat);
    mat_dtor(self);
    return self;
}

const Class Matrix = {sizeof(matrix), ctor, dtor};

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

    // printf("Enter row and column of matrix seperated by space: ");
    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    mat->row = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
    mat->col = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
    // printf("\n");

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
    mat_dtor(mat_to);
    mat_ctor(mat_to);
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
    mat_dtor(mat_to);
    mat_ctor(mat_to);
    mat_cp(mat_from, mat_to);
    mat_dtor(mat_from);
}

// Checks if all the elements of matrix are integers
static bool is_integer_matrix(matrix *mat) {
    for (long long i = 0; i < mat->row; ++i) {
        for (long long j = 0; j < mat->col; ++j) {
            if (mat->mat[i][j] - floorl(mat->mat[i][j]) != 0) {
                return false;
            }
        }
    }

    return true;
}

// Matrix print
void mat_print(matrix *mat) {
    // printf("\n");
    if (is_integer_matrix(mat)) {
        printf("[");
        for (long long i = 0; i < mat->row; ++i) {
            printf("[");
            for (long long j = 0; j < mat->col; ++j) {
                (j < mat->col - 1) ? printf("%.0Lf, ", mat->mat[i][j])
                                   : printf("%.0Lf]", mat->mat[i][j]);
            }

            if (i < mat->row - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        return;
    }

    printf("[");
    for (long long i = 0; i < mat->row; ++i) {
        printf("[");
        for (long long j = 0; j < mat->col; ++j) {
            (j < mat->col - 1) ? printf("%Lf, ", mat->mat[i][j])
                               : printf("%Lf]", mat->mat[i][j]);
        }

        if (i < mat->row - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Matrix pretty print
void mat_pprint(matrix *mat) {
    // printf("\n");
    if (is_integer_matrix(mat)) {
        for (long long i = 0; i < mat->row; ++i) {
            for (long long j = 0; j < mat->col; ++j) {
                (j < mat->col - 1) ? printf("\t%.0Lf", mat->mat[i][j])
                                   : printf("\t%.0Lf\n", mat->mat[i][j]);
            }
        }
        return;
    }

    for (long long i = 0; i < mat->row; ++i) {
        for (long long j = 0; j < mat->col; ++j) {
            (j < mat->col - 1) ? printf("\t%Lf", mat->mat[i][j])
                               : printf("\t%Lf\n", mat->mat[i][j]);
        }
    }
}

// Checks if the matrix is square or not
static bool is_square_matrix(matrix *mat) {
    if (is_valid_matrix(mat) && mat->col == mat->row) {
        return true;
    }

    return false;
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
    if (!is_valid_matrix(mat)) {
        return;
    }

    if (is_square_matrix(mat)) {
        for (long long i = 0; i < mat->row; ++i) {
            for (long long j = 0; j < i; ++j) {
                long double temp = mat->mat[i][j];
                mat->mat[i][j] = mat->mat[j][i];
                mat->mat[j][i] = temp;
            }
        }

        return;
    }

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

// Matrix scalar multiplication
void scalar_mul(matrix *mat, long double num) {
    if (is_valid_matrix(mat)) {
        for (long long i = 0; i < mat->row; ++i) {
            for (long long j = 0; j < mat->col; ++j) {
                mat->mat[i][j] *= num;
            }
        }
    }
}

// Make an identity matrix
void init_identity_matrix(matrix *mat, long long num) {
    if (num > 0) {
        mat_dtor(mat);
        mat_ctor(mat);

        mat->row = mat->col = num;

        mat_alloc(mat);

        for (long long i = 0; i < mat->row; ++i) {
            mat->mat[i][i] = 1;
        }
    }
}

// Multiply one matrix with another
void matrix_multiply(matrix *A, matrix *B) {
    if (is_valid_matrix(A) && is_valid_matrix(B) && A->col == B->row) {
        matrix temp;
        mat_ctor(&temp);
        mat_mv(A, &temp);

        A->row = temp.row;
        A->col = B->col;

        mat_alloc(A);
        for (long long i = 0; i < temp.row; ++i) {
            for (long long j = 0; j < B->col; ++j) {
                long double sum = 0;
                for (long long k = 0; k < B->row; ++k) {
                    sum += temp.mat[i][k] * B->mat[k][j];
                }
                A->mat[i][j] = sum;
            }
        }

        mat_dtor(&temp);
    }
}

// Function to get cofactor of mat[p][q] in temp
static void get_cofactor(matrix *mat, matrix *temp, long long p, long long q) {
    long long i = 0;
    long long j = 0;

    for (long long row = 0; row < mat->row; row++) {
        for (long long col = 0; col < mat->col; col++) {
            if (row != p && col != q) {
                temp->mat[i][j++] = mat->mat[row][col];

                if (j == mat->row - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Find determinant of the square matrix
long double det(matrix *mat) {
    if (is_square_matrix(mat) == 0 || is_valid_matrix(mat) == 0) {
        return 0;
    }

    long double D = 0;

    // Base case : if matrix contains single element
    if (mat->row == 1) {
        return mat->mat[0][0];
    }

    matrix temp;
    mat_ctor(&temp);

    temp.row = temp.col = mat->row - 1;
    mat_alloc(&temp);

    int sign = 1;

    for (long long f = 0; f < mat->row; f++) {
        get_cofactor(mat, &temp, 0, f); // Getting Cofactor of mat[0][f]
        D += sign * mat->mat[0][f] * det(&temp);

        sign = -sign; // terms are to be added with alternate sign
    }

    mat_dtor(&temp);

    return D;
}

// Finds the adjoint of mat and store in adj
void mat_adj(matrix *mat, matrix *adj) {
    if (!is_square_matrix(mat)) {
        return;
    }

    mat_dtor(adj);
    mat_ctor(adj);

    adj->col = adj->row = mat->row;

    mat_alloc(adj);

    for (long long i = 0; i < mat->row; ++i) {
        for (long long j = 0; j < mat->col; ++j) {
            matrix temp;
            mat_ctor(&temp);
            temp.row = temp.col = mat->row - 1;
            mat_alloc(&temp);

            get_cofactor(mat, &temp, i, j);
            int sign = ((i + j) % 2 == 0) ? 1 : -1;

            adj->mat[i][j] = sign * det(&temp);

            mat_dtor(&temp);
        }
    }

    transpose(adj);
}

// Finds the inverse of the mat and stores in inv
void mat_inv(matrix *mat, matrix *inv) {
    long double d = det(mat);
    if (d == 0) {
        return;
    }

    mat_dtor(inv);
    mat_ctor(inv);

    inv->col = inv->row = mat->row;
    mat_alloc(inv);

    matrix adj;
    mat_ctor(&adj);
    mat_adj(mat, &adj);

    scalar_mul(&adj, 1 / d);

    mat_mv(&adj, inv);
}

// Checks the equality of matrix A and B
bool matrix_equality(matrix *A, matrix *B) {
    if (is_valid_matrix(A) && is_valid_matrix(B) && A->row == B->row &&
        A->col == B->col) {
        for (long long i = 0; i < A->row; ++i) {
            for (long long j = 0; j < A->col; ++j) {
                if (A->mat[i][j] != B->mat[i][j]) {
                    return false;
                }
            }
        }
    }

    return true;
}
