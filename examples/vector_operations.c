/* Vector Operations */

#include "../src/alat.h"

void main(int argc, char *argv[])
{
   int i;

   vector_t fvector = {.dim=3, .vector={-4, 1, 6}, .coor = cartesian};
   vector_t svector = {.dim=3, .vector={6, 85, 135}, .coor = spherical};
   vector_t tvector;

   printf("First vector:\n");
   for (i = 0; i < fvector.dim; i++)
      printf("%.4f  ", fvector.vector[i]);
   printf("\n\n");

   printf("Second vector:\n");
   for (i = 0; i < svector.dim; i++)
      printf("%.4f  ", svector.vector[i]);
   printf("\n\n");

   svector = alat_vector_pow(svector, 2, cartesian);

   printf("Power of second vector:\n");
   for (i = 0; i < svector.dim; i++)
      printf("%.4f  ", svector.vector[i]);
   printf("\n\n");

   tvector = alat_vector_cross_mul(fvector, svector, cartesian);

   printf("Cross multiplication of first and second vectors:\n");
   for (i = 0; i < tvector.dim; i++)
      printf("%.4f  ", tvector.vector[i]);
   printf("\n\n");

   tvector = alat_vector_sqrt(tvector, cartesian);

   printf("Square root of third vector:\n");
   for (i = 0; i < tvector.dim; i++)
      printf("%.4f  ", tvector.vector[i]);
   printf("\n\n");

   printf("Angle between first and second vectors (deg): %f\n",
      alat_vector_angle(fvector, svector, degrees));

   exit(EXIT_SUCCESS);
}