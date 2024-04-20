/* Vector Properties in ALAT (Advanced Linear Algebra Toolkit) */

#include "../include/vectors.h"

void main(int argc, char *argv[]) {

   vector_t vector1 = { .coor = CARTESIAN,   // cartesian coordinate
                        .dim = 3,            // dimension of vector
                        .vector = {7, 4, -1} // x, y, z
                      };
   vector_t vector2 = { .coor = CYLINDRICAL, // cylindrical coordinate
                        .dim = 3,            // dimension of vector
                        .vector = {8, 120, -6} // r, fi, z
                      };
   vector_t vector3 = { .coor = SPHERICAL,   // spherical coordinate
                        .dim = 3,            // dimension of vector
                        .vector = {8, 60, 120} // r, fi, tetha
                      };

   // Transform the vector in one coordinate to another.
   vector_t res1 = transform(vector1, SPHERICAL);

   // Make some vector operations.
   double res2 = lenght(vector1);
   vector_t res3 = unit(vector1);
   vector_t res4 = cross_mul(vector1, transform(vector2, CARTESIAN));
   double res5 = distance(vector1, transform(vector3, CARTESIAN));
   double res6 = angle(DEGREES, vector1, transform(vector2, CARTESIAN));

   // Check the vector properties.
   boolean res7 = iscs(vector1, transform(vector3, CARTESIAN));
   boolean res8 = istriangle(vector1, transform(vector2, CARTESIAN));
   boolean res9 = ispythag(vector1, transform(vector2, CARTESIAN));

   __display_vector__(res1);
   printf("\n");

   printf("Lenght of vector: %f\n", res2);
   printf("\n");

   __display_vector__(res3);
   printf("\n");

   __display_vector__(res4);
   printf("\n");

   printf("Distance betwwen vectors (br): %f\n", res5);
   printf("Angle between vectors (degrees): %f\n", res6);
   printf("Is there Cauchy-Schwarz inequality: %d\n", res7);
   printf("Is there triangular inequality: %d\n", res8);
   printf("Is there pythagorean inequality: %d\n", res9);
}