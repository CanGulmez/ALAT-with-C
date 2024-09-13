/* Utils for ALAT (Advanced Linear Algebra Toolkit) */

#ifndef UTILS_H
#define UTILS_H

/* Standard C libraries */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* Global constants */

#define ROW       64
#define COL       64
#define LEN       ROW * COL
 
#define DEG(rad)              (rad * 180.0 / M_PI)
#define RAD(deg)              (deg * M_PI / 180.0)

#define raise_error(err_msg)   do {                                       \
   fprintf(stderr, "*** %s (%s::%d) ***\n", err_msg, __FILE__, __LINE__); \
   exit(EXIT_FAILURE);                                                    \
} while (0)

/* User-defined data types */

typedef unsigned int row_t; 
typedef unsigned int col_t; 
typedef unsigned int dim_t;
typedef double mat_t;
typedef double vec_t;
typedef double com_t;
typedef char * str_t;

/* User-defined enumerations */

typedef enum {
   false, 
   true, 
} bool_t;

/* User-deined stuctures */

typedef struct {
   row_t row;                 // row of matrix
   col_t col;                 // column of matrix
} shape_t;
 
typedef struct {
   shape_t shape;             // shape of matrix (row, col)
   mat_t matrix[ROW][COL];    // matrix itself
} matrix_t;

typedef struct {
   dim_t dim;                  // Dimension of vector
   vec_t vector[LEN];          // Vector itself
} vector_t;

typedef struct {
   str_t form;                 // Form of complex number (cartesian or polar)
   com_t complex[2];           // Complex number itself
} complex_t;

/* Matrix methods */

bool_t matrices_issquare(matrix_t matrix);                       
bool_t matrices_ishomogen(matrix_t matrix);                      
bool_t matrices_iszeros(matrix_t matrix);                        
bool_t matrices_isones(matrix_t matrix);                         
bool_t matrices_isarbitrary(matrix_t matrix, double value);      
bool_t matrices_isidentity(matrix_t matrix);                     
bool_t matrices_islowertri(matrix_t matrix);                     
bool_t matrices_isuppertri(matrix_t matrix);
bool_t matrices_isdiagonal(matrix_t matrix);   
bool_t matrices_issymmetric(matrix_t matrix);
bool_t matrices_isequal(matrix_t fmatrix, matrix_t smatrix);     
bool_t matrices_istriangle(matrix_t matrix);                     
bool_t matrices_isinvertible(matrix_t matrix);                   
matrix_t matrices_zeros(shape_t shape);                          
matrix_t matrices_ones(shape_t shape);                           
matrix_t matrices_identity(shape_t shape);                       
matrix_t matrices_arbitrary(double value, shape_t shape);        
matrix_t matrices_sequential(int start, int end, shape_t shape); 
matrix_t matrices_random(shape_t shape);                        
matrix_t matrices_uniform(int start, int end, shape_t shape);   
matrix_t matrices_randint(int start, int end, shape_t shape);  
matrix_t matrices_diagonal(matrix_t matrix);          
double matrices_max(matrix_t matrix);                 
double matrices_min(matrix_t matrix);                 
shape_t matrices_elmax(matrix_t matrix, bool_t reverse);              
shape_t matrices_elmin(matrix_t matrix, bool_t reverse);              
double matrices_mean(matrix_t matrix);                
double matrices_stddev(matrix_t matrix);              
double matrices_median(matrix_t matrix);              
matrix_t matrices_pow(matrix_t matrix, double n);                    
matrix_t matrices_root(matrix_t matrix, double n);          
matrix_t matrices_degrees(matrix_t matrix);
matrix_t matrices_radians(matrix_t matrix);
matrix_t matrices_sort(matrix_t matrix_t, bool_t reverse);
matrix_t matrices_sum(matrix_t matrix, int axis);                 
matrix_t matrices_shuffle(matrix_t matrix);                             
matrix_t matrices_abs(matrix_t matrix);                                 
matrix_t matrices_reshape(matrix_t matrix_t, shape_t shape);            
matrix_t matrices_transpose(matrix_t matrix);                           
matrix_t matrices_concat(matrix_t fmatrix, matrix_t smatrix, int axis); 
matrix_t matrices_add(matrix_t fmatrix, matrix_t smatrix);              
matrix_t matrices_subtract(matrix_t fmatrix, matrix_t smatrix);         
matrix_t matrices_scaler_mul(matrix_t matrix, double scaler);           
matrix_t matrices_dot_mul(matrix_t fmatrix, matrix_t smatrix);          
matrix_t matrices_cross_mul(matrix_t fmatrix, matrix_t smatrix);        
matrix_t matrices_scaler_div(matrix_t matrix, double scaler);           
matrix_t matrices_swap(matrix_t matrix);                                
matrix_t matrices_dot_div(matrix_t fmatrix, matrix_t smatrix);          
double matrices_det(matrix_t matrix);
matrix_t matrices_minors(matrix_t matrix);
matrix_t matrices_cofactors(matrix_t matrix);
matrix_t matrices_adjoint(matrix_t matrix);
matrix_t matrices_inverse(matrix_t matrix);
matrix_t matrices_solve(matrix_t matrix);  

/* Vector methods */

bool_t vectors_iszeros(vector_t vector);
bool_t vectors_isones(vector_t vector);
bool_t vectors_isequal(vector_t fvector, vector_t svector);
bool_t vectors_isarbitrary(vector_t vector, double value);
bool_t vectors_iscasc(vector_t fvector, vector_t svector);
bool_t vectors_istriangle(vector_t fvector, vector_t svector);
bool_t vectors_ispythagorean(vector_t fvector, vector_t svector);
bool_t vectors_isstep(vector_t fvector, vector_t svector);
bool_t vectors_isparallel(vector_t fvector, vector_t svector);
vector_t vectors_zeros(dim_t dim);
vector_t vectors_ones(dim_t dim);
vector_t vectors_arbitrary(double value, dim_t dim);
vector_t vectors_sequential(int start, int end, dim_t dim);
vector_t vectors_random(dim_t dim);
vector_t vectors_uniform(int start, int end, dim_t dim);
vector_t vectors_transform(vector_t vector, str_t old_coor, str_t new_coor);
double vectors_lenght(vector_t vector);
vector_t vectors_abs(vector_t vector);
vector_t vectors_pow(vector_t vector, double n);
vector_t vectors_root(vector_t vector, double n); 
vector_t vectors_unit(vector_t vector);
vector_t vectors_add(vector_t fvector, vector_t svector);
vector_t vectors_subtract(vector_t fvector, vector_t svector);
vector_t vectors_scaler_mul(vector_t vector, double scaler);
double vectors_distance(vector_t fvector, vector_t svector);
double vectors_dot_mul(vector_t fvector, vector_t svector);
vector_t vectors_cross_mul(vector_t fvector, vector_t svector);
double vectors_angle(vector_t fvector, vector_t svector, str_t form);

/* Complex number methods */

bool_t complexes_iscartesian(complex_t complex);
bool_t complexes_ispolar(complex_t complex);
bool_t complexes_iszero(complex_t complex);
bool_t complexes_istriangle(complex_t fcomplex, complex_t scomplex);
bool_t complexes_isequal(complex_t fcomplex, complex_t scomplex);
complex_t complexes_zero(str_t output_form);
complex_t complexes_transform(complex_t complex, str_t new_form);
double complexes_real(complex_t complex);
double complexes_imaginary(complex_t complex);
double complexes_modules(complex_t complex);
double complexes_argument(complex_t complex);
complex_t complexes_add(complex_t fcomplex, complex_t scomplex, str_t output_form);
complex_t complexes_subtract(complex_t fcomplex, complex_t scomplex, str_t output_form);
complex_t complexes_multiply(complex_t fcomplex, complex_t scomplex, str_t output_form);
complex_t complexes_divide(complex_t fcomplex, complex_t scomplex, str_t output_form);
complex_t complexes_power(complex_t complex, double n, str_t output_form);
complex_t complexes_root(complex_t complex, double n, str_t output_form);
complex_t complexes_conjugate(complex_t complex, str_t output_form);
complex_t complexes_reciprocol(complex_t complex, str_t output_form);

/* Cryptography methods */

matrix_t crypts_to_matrix(str_t message, shape_t shape);
matrix_t crypts_encode(str_t message, matrix_t encoder);
matrix_t crypts_decode(matrix_t encoded, matrix_t encoder);
str_t crypts_to_message(matrix_t encoded, matrix_t encoder);

/* Application methods */

vector_t apps_poly_curve_fitting(vector_t xvector, vector_t yvector);
vector_t apps_least_sqaures_reg(vector_t xvector, vector_t yvector);
double apps_area(vector_t xvector, vector_t yvector);
double apps_volume(vector_t xvector, vector_t yvector, vector_t zvector);

#endif /* UTILS_H */
