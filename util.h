
#if !defined(UTIL_H)
#define UTIL_H 1

#include "matrix.h"

// Checks if the column is zero
bool is_zero_col(matrix *mat, long num);

// Checks if the row is zero
bool is_zero_row(matrix *mat, long num);

// Multiply a row by a scalar
void row_scalar_mul(matrix *mat, long num, long double mul);

#endif // UTIL_H
