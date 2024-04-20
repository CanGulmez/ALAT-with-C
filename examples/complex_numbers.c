/* Complex number examples in ALAT (Advanced Linear Algebra Toolkit) */

#include "../include/complexes.h"

void main(int argc, char *argv[]) {

   complex_t complex1 = { .form = CARTESIAN,  // cartesian form
                          .complex = {3, 4},  // 3 + j4
                        };
   complex_t complex2 = { .form = POLAR,        // polar form
                          .complex = {5, 53.13} // r=5, tetha=53.13
                        };
   
   // Transform the complex number in one form to another.
   complex_t res1 = transform(complex2, CARTESIAN);
   
   __display_complex__(res1);
   printf("\n");

   // Compare the complex numbers.
   if (isequal(complex1, complex2))
      printf("These complex numbers are equal.\n");
   else
      printf("These complex numbers are not equal.\n");
   printf("\n");

   // Make some complex number operations.
   complex_t res2 = multiply(complex1, complex1);
   complex_t res3 = conjugate(complex2);
   complex_t res4 = power(complex1, 5);
   complex_t res5 = root(complex1, 5);

   __display_complex__(res2);
   printf("\n");

   __display_complex__(res3);
   printf("\n");

   __display_complex__(res4);
   printf("\n");

   __display_complex__(res5);
}