/* Multiply complex numbers */

#include "../source/alat.h"

void main(int argc, char *argv[])
{
   // Indicate the two complex numbers in two different form. Note 
   // that for cartesian form, complex will be {real, imaginary}, 
   // for polar form, complex will be {modules, argument}.
   complex_t fcomplex = {.complex = {3, 8}, .form = "cartesian"};
   complex_t scomplex = {.complex = {-8, 90}, .form = "polar"};

   // Multiply the these complex number. (Doesn't matter forms).
   complex_t result = complexes_multiply(
      fcomplex, 
      scomplex, 
      "cartesian"    /* output form can be "cartesian" or "polar" */
   );

   printf("real: %f, imaginary: %f, form: %s\n",
      result.complex[0], result.complex[1], result.form);

   exit(EXIT_SUCCESS);
}
