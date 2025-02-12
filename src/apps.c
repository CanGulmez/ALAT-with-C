/* Some applications in ALAT (Advanced Linear Algebra Toolkit) */

#include "./alat.h"

/**
 * Apply polynomial curve fitting using both `xpoints` and `ypoints` which are 
 * respectively x and y axis points where related-function passes. For example, if
 * x any y exis points are {1, -4, 5} and {-4, 1, -2} in order. The output will be
 * {-3.67, -0.5, 0.17} which means `f(x) = 0.17x^2 - 0.5x - 3.67`.
 */
points_t alat_app_poly_curve_fitting(points_t xpoints, points_t ypoints)
{
   int i, j;
   matrix_t main, target, mvector, muled;
   points_t result; 

   assert_points(xpoints);
   assert_points(ypoints);
   assert (xpoints.length == ypoints.length);

   mvector.shape.row = 1, mvector.shape.col = ypoints.length;
   for (i = 0; i < ypoints.length; i++)
      mvector.matrix[0][i] = ypoints.points[i];
   
   main = alat_matrix_zeros((shape_t) {xpoints.length, ypoints.length});
   target = alat_matrix_transpose(mvector);

   for (i = 0; i < xpoints.length; i++) 
      for (j = 0; j < xpoints.length; j++) 
         main.matrix[i][j] = pow(xpoints.points[i], j);

   muled = alat_matrix_cross_mul(alat_matrix_inverse(main), target);
   result.length = xpoints.length;

   for (i = 0; i < result.length; i++)
      result.points[i] = muled.matrix[i][0];

   return result;
}

/**
 * Apply least squares regression using both `xpoints` and `ypoints` which 
 * are respectively x and y axis points where related-function passes.
 */
points_t alat_app_least_sqaures_reg(points_t xpoints, points_t ypoints)
{
   int i;
   shape_t shape;
   matrix_t main, target, muled;
   points_t result;

   assert_points(xpoints);
   assert_points(ypoints);
   assert (xpoints.length == ypoints.length);

   result.length = 2;
   target.shape = (shape_t) {1, ypoints.length};
   main = alat_matrix_ones((shape_t) {2, xpoints.length});

   for (i = 0; i < xpoints.length; i++)
      main.matrix[1][i] = xpoints.points[i];
   for (i = 0; i < ypoints.length; i++)
      target.matrix[0][i] = ypoints.points[i];

   muled = alat_matrix_scalar_mul(alat_matrix_cross_mul(alat_matrix_cofactors(
      alat_matrix_cross_mul(main, alat_matrix_transpose(main))), 
      alat_matrix_cross_mul(main, alat_matrix_transpose(target))), 0.02);
   result.points[0] = muled.matrix[0][0], result.points[1] = muled.matrix[1][0];

   return result;
}

/**
 * Calculate the area of triangle using determinant where 
 * corners of that triangle are in `xpoints` and `ypoints`.
 */
double alat_app_area(points_t xpoints, points_t ypoints)
{
   int i;
   matrix_t main;
   double result;

   assert_points(xpoints);
   assert_points(ypoints);
   assert (xpoints.length == 3 && ypoints.length == 3);

   main = alat_matrix_ones((shape_t) {3, 3});

   for (i = 0; i < xpoints.length; i++) 
      main.matrix[0][i] = xpoints.points[i],
      main.matrix[1][i] = ypoints.points[i];
 
   result = alat_matrix_det(alat_matrix_transpose(main)) / 2.0;

   return (result < 0) ? (-1.0 * result) : result;
}

/**
 * Calculate the volume of tetrahedron using determinant where corners
 * of that tetrahedron are in `xpoints`, `ypoints` and `zpoints.`
 */
double alat_app_volume(points_t xpoints, points_t ypoints, points_t zpoints)
{
   int i;
   matrix_t main;
   double result;

   assert_points(xpoints);
   assert_points(ypoints);
   assert_points(zpoints);
   assert (xpoints.length == 4 && ypoints.length == 4 && zpoints.length == 4);

   main = alat_matrix_ones((shape_t) {4, 4});

   for (i = 0; i < xpoints.length; i++) 
      main.matrix[0][i] = xpoints.points[i],
      main.matrix[1][i] = ypoints.points[i],
      main.matrix[2][i] = zpoints.points[i];

   result = alat_matrix_det(alat_matrix_transpose(main)) / 6.0;

   return (result < 0) ? (-1.0 * result) : result;
}
