
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

// Base Structure of Matrix
typedef struct matrix {
    long row;
    long col;

    long double **data;
} matrix;

// Structure to store pivots of RREF
typedef struct pivot_data {
    long num_pivots;
    long *pivot_arr;
} pivot_data;

// Structure to bind RREF and its pivots
typedef struct aug_mat {
    matrix *rref;
    pivot_data *piv;
} aug_mat;

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

// Matrix copy
matrix *mat_cp(matrix *mat);

// Transpose the matrix
matrix *transpose(matrix *mat);

// A * x = b
aug_mat *solve(matrix *A, matrix *b);

// Return a matrix of ones
matrix *ones(long row, long col);

// Return a matrix of zeros
matrix *zeros(long row, long col);

// Return an identity matrix
matrix *eye(long row, long col);

// Return [A b]
matrix *aug(matrix *A, matrix *b);

// pivotdata deleter
void piv_del(pivot_data *piv);

// Augmented Matrix deleter
void aug_del(aug_mat *m);

// Calculate the nullspace of matrix
matrix *nullspace(aug_mat *mat, long num_aug_col);

// Checks and returns the solution set
void solution(aug_mat *mat, matrix *nullmat);

#endif // MATRIX_H
