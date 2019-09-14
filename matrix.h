
// dhruvil
// Mon 27 May 2019 08:57:14 PM IST
// matrix.h

#if !defined(MATRIX_H)
#define MATRIX_H 1

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix {
    long row;
    long col;

    long double **data;
} matrix;

// Matrix initializer
matrix *mat_init(void);

// Matrix deleter
void mat_del(matrix *mat);

// Matrix pretty print
void mat_print(matrix *mat);

// Print augmented matrix
void mat_print_aug(matrix *mat, long col);

// Swap the columns
void swap_cols(matrix *mat, long col1, long col2);

// Swap the rows
void swap_rows(matrix *mat, long row1, long row2);

// Clean the current memory and user input new matrix
void mat_input(matrix *mat);

// Transpose the matrix
matrix *transpose(matrix *mat);

// Reduced Row Echelon Form
matrix *rref(matrix *A);

// Return a matrix of ones
matrix *ones(long row, long col);

// Return a matrix of zeros
matrix *zeros(long row, long col);

// Return an identity matrix
matrix *eye(long row, long col);

// Return [A b]
matrix *aug(matrix *A, matrix *b);

#endif // MATRIX_H
