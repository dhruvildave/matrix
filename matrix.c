
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

static void swap(long double *x, long double *y) {
    long double temp = *x;
    *x = *y;
    *y = temp;
}

long double det(matrix *mat) {
    if (is_square_matrix(mat) == 0) {
        return 0;
    }

    matrix new;
    mat_ctor(&new);
    mat_cp(mat, &new);

    long double det = 1;
    long double total = 1; // Initialize result
    // temporary array for storing row
    // long double temp[mat->row];

    // loop for traversing the diagonal elements
    for (long long i = 0; i < new.row; i++) {
        long long index = i; // intialize the index

        // finding the index which has non zero value
        while (index < new.row &&new.mat[index][i] == 0) {
            index++;
        }

        // if there is non zero element
        if (index == new.row) {
            continue; // the determinant of matrix as zero
        }

        if (index != i) {
            // loop for swaping the diagonal element row and index row
            for (long long j = 0; j < new.row; j++) {
                swap(&new.mat[index][j], &new.mat[i][j]);

                // determinant sign changes when we shift rows
                // go through determinant properties
                det *= pow(-1, index - i);
            }
        }

        long double temp[new.row];
        // storing the values of diagonal row elements
        for (long long j = 0; j < new.row; j++) {
            temp[j] = new.mat[i][j];
        }

        // traversing every row below the diagonal element
        for (long long j = i + 1; j < new.row; j++) {
            long double num1 = temp[i];       // value of diagonal element
            long double num2 = new.mat[j][i]; // value of next row element

            // traversing every column of row and multiplying to every row
            for (long long k = 0; k < new.row; k++) {
                // multiplying to make the diagonal
                // element and next row element equal
                new.mat[j][k] = (num1 * new.mat[j][k]) - (num2 * temp[k]);
            }

            total *= num1; // Det(kA)=kDet(A);
        }
    }

    // multiplying the diagonal elements to get determinant
    for (long long i = 0; i < new.row; i++) {
        det *= new.mat[i][i];
    }

    mat_dtor(&new);

    return (det / -total); // Det(kA)/k=Det(A);}
}
