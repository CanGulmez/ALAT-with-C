// Matrix creating examples in ALAT (Advanced Linear Algebra Toolkit)

#include "../include/matrices.h"

void main(int argc, char *argv) {

   // Create the matrices.
   matrix_t res1 = zeros(3, 4);
   matrix_t res2 = ones(3, 4);
   matrix_t res3 = identity(4, 4);
   matrix_t res4 = arbitrary(-5, 4, 4);
   matrix_t res5 = sequential(0, 100, 5, 5);
   matrix_t res6 = randouble(-10, 10, 4, 4);

   // Display the created matrices.
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
}