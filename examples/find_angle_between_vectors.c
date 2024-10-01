/* Find the angle between two vectors */

#include "../source/alat.h"

void main(int argc, char *argv[])
{
   // Create two vectors randomly.
   vector_t fvector = vectors_random(5);
   vector_t svector = vectors_uniform(-10, 10, 5);

   printf("First vector: \n");
   for (int i = 0; i < fvector.dim; i++)
      printf("%f ", fvector.vector[i]);
   printf("\n");

   printf("Second vector: \n");
   for (int i = 0; i < svector.dim; i++)
      printf("%f ", svector.vector[i]);
   printf("\n");

   // Calculate the angle between these vectors in three form.
   printf("Angle between these vectors: ");
   printf("%f (decimal), %f (radians), %f (degrees)\n", 
      vectors_angle(fvector, svector, "decimal"),   
      vectors_angle(fvector, svector, "radians"),   
      vectors_angle(fvector, svector, "degrees")  
   );

   exit(EXIT_SUCCESS);
}