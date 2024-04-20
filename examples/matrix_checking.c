// Matrix checking examples in ALAT (Advanced Linear Algebra Toolkit)

#include "../include/matrices.h"

void main(int argc, char *argv) {

   // Create the new matrix objects for checking its properties.
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
                           {1, 0, 0, 0}, 
                           {0, 1, 0, 0}, 
                           {0, 0, 1, 0}, 
                           {0, 0, 0, 1}, 
                        }
                      };

   // Check the matrix properties.
   boolean res1 = ishomogen(matrix1);
   boolean res2 = iszeros(matrix1);
   boolean res3 = isones(matrix2);
   boolean res4 = isidentity(matrix2);
   boolean res5 = isequal(matrix1, matrix2);
   boolean res6 = islowertri(matrix2);
   boolean res7 = isuppertri(matrix2);
   boolean res8 = isinvertible(matrix1);

   // Display the checked matrix properties.
   printf("Is matrix homojen: %d\n", res1);
   printf("Is matrix zeros: %d\n", res2);
   printf("Is matrix ones: %d\n", res3);
   printf("Is matrix identity: %d\n", res4);
   printf("Are both matrices equal: %d\n", res5);
   printf("Is matrix lower triangular: %d\n", res6);
   printf("Is matrix upper triangular: %d\n", res7);
   printf("Is matrix is invertible: %d\n", res8);
}