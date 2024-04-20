// Matrix operation examples in ALAT (Advanced Linear Algebra Toolkit)

#include "../include/matrices.h"

void main(int argc, char *argv) {

   // Create the new matrix objects for making four transactions.
   matrix_t matrix1 = { .row = 4, 
                        .col = 4, 
                        .matrix = {
                           {7, 0, 0, -6}, 
                           {-8, -7, 0, 0}, 
                           {5, 4, 7, 0}, 
                           {-3, 0, -1, -8}, 
                        }
                      };
   matrix_t matrix2 = { .row = 4, 
                        .col = 4, 
                        .matrix = {
                           {1, -5, 0, -8}, 
                           {0, 0, 0, -1}, 
                           {8, 4, 4, 0}, 
                           {8, 3, 0, 1}, 
                        }
                      };

   // Make some the matrix four transactons.
   matrix_t res1 = add(matrix1, matrix2);
   matrix_t res2 = subtract(matrix1, matrix2);
   matrix_t res3 = scaler_mul(-4.8, matrix2);
   matrix_t res4 = dot_mul(matrix1, matrix2);
   matrix_t res5 = cross_mul(matrix1, matrix2);
   matrix_t res6 = scaler_div(-2.0, matrix2);
   matrix_t res7 = dot_div(matrix1, matrix2);

   // Display the results.
   __display_matrix__(res1);
   printf("\n");

   __display_matrix__(res2);
   printf("\n");

   __display_matrix__(res3);
   printf("\n");

   __display_matrix__(res4);
   printf("\n");

   __display_matrix__(res5);
   printf("\n");

   __display_matrix__(res6);
   printf("\n");

   __display_matrix__(res7);
}