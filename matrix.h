
// dhruvil
// Mon 27 May 2019 08:57:14 PM IST
// matrix.h

#if !defined(MATRIX_H)
#define MATRIX_H 1

#include "new/new.h"

typedef struct matrix {
    const void *cls;

    long long row;
    long long col;

    long double **mat;
} matrix;

const Class Matrix;

// Matrix constructor
void mat_ctor(matrix *gph);

// Matrix destructor
void mat_dtor(matrix *gph);

// Matrix initializer
void mat_init(matrix *mat);

// Matrix allocator
void mat_alloc(matrix *mat);

// Matrix copy
void mat_cp(matrix *mat_from, matrix *mat_to);

// Matrix move
void mat_mv(matrix *mat_from, matrix *mat_to);

// Matrix print
void mat_print(matrix *mat);

// Matrix pretty print
void mat_pprint(matrix *mat);

// Matrix addition
void add(matrix *addend0, matrix *addend1);

// Matrix substraction
void sub(matrix *subend0, matrix *subend1);

// Matrix transpose
void transpose(matrix *mat);

// Matrix scalar multiplication
void scalar_mul(matrix *mat, long double num);

// Matrix multiplication
void matrix_multiply(matrix *A, matrix *B);

// Make an identity matrix
void init_identity_matrix(matrix *mat, long long num);

// Find determinant of the square matrix
long double det(matrix *mat);

// Finds the adjoint of mat and store in adj
void adj(matrix *mat, matrix *adj);

// Finds the inverse of the mat and stores in inv
void mat_inv(matrix *mat, matrix *inv);

// Checks the equality of matrix A and B
bool matrix_equality(matrix *A, matrix *B);

#endif // MATRIX_H
