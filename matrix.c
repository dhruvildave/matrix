
// dhruvil
// Mon 27 May 2019 10:49:37 PM IST
// matrix.c

#include "matrix.h"
#include "pch.h"
#include <math.h>

// Matrix constructor
void mat_ctor(matrix *mat) {
    mat->col = mat->row = -1;

    mat->mat = NULL;
}

// Matrix destructor
void mat_dtor(matrix *mat) {
    if (mat->col >= 0 && mat->row >= 0) {
        mat->col = mat->row = -1;
        free(mat->mat);
        mat->mat = NULL;
    }
}

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

    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    mat->row = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
    mat->col = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);

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

// Checks the validity of matrix
static int is_valid_matrix(matrix *mat) {
    if (mat->row > 0 && mat->col > 0 && mat->mat != NULL) {
        return 1;
    }

    return 0;
}

// Matrix copy
void mat_cp(matrix *mat_from, matrix *mat_to) {
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
    mat_cp(mat_from, mat_to);
    mat_dtor(mat_from);
}

// Checks if all the elements of matrix are integers
static int is_integer_matrix(matrix *mat) {
    for (long long i = 0; i < mat->row; ++i) {
        for (long long j = 0; j < mat->col; ++j) {
            if (mat->mat[i][j] - floorl(mat->mat[i][j]) != 0) {
                return 0;
            }
        }
    }

    return 1;
}

// Matrix print
void print(matrix *mat) {
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
    } else {
        printf("[");
        for (long long i = 0; i < mat->row; ++i) {
            printf("[");
            for (long long j = 0; j < mat->col; ++j) {
                (j < mat->col - 1) ? printf("%.2Lf, ", mat->mat[i][j])
                                   : printf("%.2Lf]", mat->mat[i][j]);
            }

            if (i < mat->row - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

// Matrix pretty print
void p_print(matrix *mat) {
    if (is_integer_matrix(mat)) {
        for (long long i = 0; i < mat->row; ++i) {
            for (long long j = 0; j < mat->col; ++j) {
                (j < mat->col - 1) ? printf("\t%.0Lf", mat->mat[i][j])
                                   : printf("\t%.0Lf\n", mat->mat[i][j]);
            }
        }
    } else {
        for (long long i = 0; i < mat->row; ++i) {
            for (long long j = 0; j < mat->col; ++j) {
                (j < mat->col - 1) ? printf("\t%.2Lf", mat->mat[i][j])
                                   : printf("\t%.2Lf\n", mat->mat[i][j]);
            }
        }
    }
}

// Checks if the matrix is square or not
static int is_square_matrix(matrix *mat) {
    if (is_valid_matrix(mat) && mat->col == mat->row) {
        return 1;
    }

    return 0;
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
    if (is_square_matrix(mat)) {
        for (long long i = 0; i < mat->row; ++i) {
            for (long long j = 0; j < i; ++j) {
                long double temp = mat->mat[i][j];
                mat->mat[i][j] = mat->mat[j][i];
                mat->mat[j][i] = temp;
            }
        }
    } else {
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
}

// Matrix scalar multiplication
void scalar_mul(matrix *mat, long long num) {
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

    // Looping for each element of the matrix
    for (long long row = 0; row < mat->row; row++) {
        for (long long col = 0; col < mat->col; col++) {
            // Copying into temporary matrix only those element
            // which are not in given row and column
            if (row != p && col != q) {
                temp->mat[i][j++] = mat->mat[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == mat->row - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive function for finding determinant of matrix.
n is current dimension of mat[][]. */
long double det(matrix *mat) {
    long double D = 0; // Initialize result

    // Base case : if matrix contains single element
    if (mat->row == 1) {
        return mat->mat[0][0];
    }

    matrix temp;
    mat_ctor(&temp);

    temp.row = temp.col = mat->row - 1;
    mat_alloc(&temp);

    int sign = 1;

    // Iterate for each element of first row
    for (long long f = 0; f < mat->row; f++) {
        get_cofactor(mat, &temp, 0, f); // Getting Cofactor of mat[0][f]
        D += sign * mat->mat[0][f] * det(&temp);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    mat_dtor(&temp);

    return D;
}
