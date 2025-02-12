/* Some Applications */

#include "../src/alat.h"

void main(int argc, char *argv[])
{
   int i;

   points_t xpoints = {.length = 4, .points = {2, 4, 7, 11}}; // x axis points
   points_t ypoints = {.length = 4, .points = {-1, 5, 8, 9}}; // y axis points


   printf("Apply polynomial curve fitting onto 'xpoints' and 'ypoints':\n");

   points_t curve = alat_app_poly_curve_fitting(xpoints, ypoints);

   for (i = curve.length - 1; i >= 0; i--)
      printf("(%.4f) * x^%d + ", curve.points[i], i);
   printf("0\n\n");

   printf("Apply least squares regression onto 'xpoints' and 'ypoints':\n");

   points_t regression = alat_app_least_sqaures_reg(xpoints, ypoints);

   for (i = regression.length - 1; i >= 0; i--)
      printf("(%.4f) * x^%d + ", regression.points[i], i);
   printf("0\n");

   exit(EXIT_SUCCESS);
}
