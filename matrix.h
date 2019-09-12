
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
    bool row_major;
    long long row;
    long long col;

    long double **data;
} matrix;

// Matrix initializer
matrix *mat_init(void);

// Matrix deleter
void mat_del(matrix *mat);

// Matrix pretty print
void mat_print(matrix *mat);

// Swap the columns
void swap_cols(matrix *mat, long col1, long col2);

// Swap the rows
void swap_rows(matrix *mat, long row1, long row2);

// Clean the current memory and user input new matrix
void mat_input(matrix *mat);

// Transpose the matrix
void transpose(matrix *mat);

#endif // MATRIX_H
