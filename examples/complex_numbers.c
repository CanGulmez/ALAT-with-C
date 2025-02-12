/* Complex Numbers */

#include "../src/alat.h"

void main(int argc, char *argv[])
{
   complex_t fcomplex = {.format=algebraic, .complex={4, 5}};
   complex_t scomplex = {.format=polar, .complex={2, 125}};
   complex_t tcomplex;

   printf("Real portion of 'scomplex': %f\n", alat_complex_real(scomplex));
   printf("Imaginary portion of 'scomplex': %f\n", alat_complex_imaginary(scomplex));
   printf("Magnitude portion of 'scomplex': %f\n", alat_complex_magnitude(fcomplex));
   printf("Argument portion of 'scomplex': %f\n", alat_complex_argument(fcomplex));

   fcomplex = alat_complex_transform(fcomplex, polar);

   tcomplex = alat_complex_mul(fcomplex, scomplex, polar);

   printf("Third complex number (in polar): (%.4f, %.4f)\n", tcomplex.complex[0], 
      tcomplex.complex[1]);

   exit(EXIT_SUCCESS);
}
