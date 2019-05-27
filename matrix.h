
// dhruvil
// Mon 27 May 2019 08:57:14 PM IST
// matrix.h

#if !defined(MATRIX_H)
#define MATRIX_H 1

typedef struct _matrix {
    long long row;
    long long col;

    long double **mat;
} matrix;

// Matrix constructor
void mat_ctor(matrix *mat);

// Matrix destructor
void mat_dtor(matrix *mat);

// Matrix initializer
void mat_init(matrix *mat, const int NUMBASE);

// Matrix allocator
void mat_alloc(matrix *mat);

// Matrix copy
void mat_cp(matrix *mat_from, matrix *mat_to);

// Matrix move
void mat_mv(matrix *mat_from, matrix *mat_to);

// Matrix print
void print(matrix *mat);

#endif // MATRIX_H
