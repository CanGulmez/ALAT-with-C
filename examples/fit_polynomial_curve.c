/* Fit the polynomial curve onto x and y axis points */

#include "../source/utils.h"

void main(int argc, char *argv[])
{
   // Indicate the x and y axis points.
   vector_t xvector = {.dim = 4, .vector = {1, 4, 6, 7}};
   vector_t yvector = {.dim = 4, .vector = {3, 7, 8, 9}};

   // Apply the polynomial curve fitting.
   vector_t result = apps_poly_curve_fitting(xvector, yvector);

   // Display the results.
   for (int i = 0; i < result.dim; i++)
      printf("%f ", result.vector[i]);

   printf("\nor\n");

   printf("f(x) = -0.33x^3 + 4.06x^2 -0.78x + 0.056\n");

   exit(EXIT_SUCCESS);
}