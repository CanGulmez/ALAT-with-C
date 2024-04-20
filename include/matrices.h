/*  Matrix Operations in ALAT (Advanced Linear Algebra Toolkit)  */

#ifndef MATRICES_H
#define MATRICES_H

// Standard C Libraries:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Global Constants:
#define ROW       32
#define COL       32
#define LEN       32*32

// New data types:
typedef unsigned int row_t;
typedef unsigned int col_t;
typedef unsigned int len_t;
typedef double arr_t;
typedef double mat_t;

// User-defined Enumeration:
typedef enum {
   false, 
   true, 
} boolean;

// User-defined Structures:
typedef struct {
   len_t len;                 // Lenght of array
   arr_t array[LEN];          // Array itself
} array_t;

typedef struct {
   row_t row;                 // Row number of matrix
   row_t col;                 // Column number of matrix
   mat_t matrix[ROW][COL];    // Matrix itself
} matrix_t;

// Helper Function Prototypes:

void __display_matrix__(matrix_t matrix);
array_t __to_array__(matrix_t matrix);
matrix_t __to_matrix__(array_t array, row_t row, col_t col);
matrix_t __copy_matrix__(matrix_t matrix);
matrix_t __delete_row__(int row, matrix_t matrix);
matrix_t __delete_col__(int col, matrix_t matrix);

// Main Function Prototypes:

matrix_t diagonal(matrix_t matrix);
boolean ishomogen(matrix_t matrix);
boolean iszeros(matrix_t matrix);
boolean isones(matrix_t matrix);
boolean isidentity(matrix_t matrix);
matrix_t zeros(row_t row, col_t col);
matrix_t ones(row_t row, col_t col);
matrix_t identity(row_t row, col_t col);
matrix_t arbitrary(double value, row_t row, col_t col);
matrix_t sequential(int start, int end, row_t row, col_t col);
matrix_t randouble(int start, int end, row_t row, col_t col);
boolean isequal(matrix_t matrix1, matrix_t matrix2);
double highest(matrix_t matrix);
double lowest(matrix_t matrix);
matrix_t agg_ver(matrix_t matrix);
matrix_t agg_hor(matrix_t matrix);
matrix_t transpose(matrix_t matrix);
boolean islowertri(matrix_t matrix);
boolean isuppertri(matrix_t matrix);
boolean istriangle(matrix_t matrix);
double mean(matrix_t matrix);
double stddev(matrix_t matrix);
double median(matrix_t matrix);
matrix_t sort_asc(matrix_t matrix);
matrix_t sort_des(matrix_t matrix);
matrix_t shuffle(matrix_t matrix);
matrix_t reshape(matrix_t matrix, row_t row, col_t col);
matrix_t concat_hor(matrix_t matrix1, matrix_t matrix2);
matrix_t concat_ver(matrix_t matrix1, matrix_t matrix2);
matrix_t add(matrix_t matrix1, matrix_t matrix2);
matrix_t subtract(matrix_t matrix1, matrix_t matrix2);
matrix_t scaler_mul(double scaler, matrix_t matrix);
matrix_t dot_mul(matrix_t matrix1, matrix_t matrix2);
matrix_t cross_mul(matrix_t matrix1, matrix_t matrix2);
matrix_t scaler_div(double scaler, matrix_t matrix);
matrix_t dot_div(matrix_t matrix1, matrix_t matrix2);
matrix_t uppertri(matrix_t matrix);
double det(matrix_t matrix);
matrix_t minors(matrix_t matrix);
matrix_t cofactors(matrix_t matrix);
boolean isinvertible(matrix_t matrix);
matrix_t adjoint(matrix_t matrix);
matrix_t inverse(matrix_t matrix);
matrix_t lowertri(matrix_t matrix);
matrix_t solve(matrix_t matrix);

#endif /* MATRICES_H */
