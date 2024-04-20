// Advanced matrix examples in ALAT (Advanced Linear Algebra Toolkit)

#include "../include/matrices.h"

void main(int argc, char *argv) {

   // Create the new matrix objects for some advanced operations.
   matrix_t matrix = { .row = 4, 
                        .col = 4, 
                        .matrix = {
                           {7, 0, 0, -6}, 
                           {-8, -7, 0, 0}, 
                           {5, 4, 7, 0}, 
                           {-3, 0, -1, -8}, 
                        }
                      };
   matrix_t linear = { .row = 3, 
                       .col = 4, 
                       .matrix = {
                           {7, 0, -1, -2}, 
                           {3, -4, -5, 0}, 
                           {5, 6, 4, 3}, 
                       } 
                     };

   // Make some advanced matrix operations.
   double res1 = det(matrix);
   matrix_t res2 = cofactors(matrix);
   matrix_t res3 = adjoint(matrix);
   matrix_t res4 = inverse(matrix);
   matrix_t res5 = minors(matrix);
   matrix_t res6 = solve(linear);

   printf("%f\n", res1);
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
}