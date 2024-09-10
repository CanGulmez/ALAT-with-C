/* Some applications in ALAT (Advanced Linear Algebra Toolkit) */

#include "./utils.h"

/**
 * Apply polynomial curve fitting application. `xvector` and `yvector`
 * are respectively x and y axis points where related-function passes.
 */
vector_t apps_poly_curve_fitting(vector_t xvector, vector_t yvector)
{
   vector_t result;
   matrix_t main, target, mvector, res;
   int i, j;

   if (xvector.dim != yvector.dim)
      raise_error("Dimension dismatch found");

   // Create the 'mvector' matrix using `yvector` points.
   mvector.shape.row = 1, mvector.shape.col = yvector.dim;
   for (i = 0; i < yvector.dim; i++)
      mvector.matrix[0][i] = yvector.vector[i];

   // Create related sub-matrices.
   main = matrices_zeros((shape_t) {xvector.dim, yvector.dim});
   target = matrices_transpose(mvector);

   // Fill the 'main' matrix using points of 'xvector'.
   for (i = 0; i < xvector.dim; i++) 
      for (j = 0; j < xvector.dim; j++) 
         main.matrix[i][j] = pow(xvector.vector[i], j);

   // Find the polynomial curve fitting in matrix form.
   res = matrices_cross_mul(matrices_inverse(main), target);

   // Convert the matrix form back to vector and return it.
   result.dim = xvector.dim;
   for (i = 0; i < result.dim; i++)
      result.vector[i] = res.matrix[i][0];

   return result;
}

/**
 * Apply least squares regression application. `xvector` and `yvector` 
 * are respectively x and y axis points where related-function passes.
 */
vector_t apps_least_sqaures_reg(vector_t xvector, vector_t yvector)
{
   vector_t result;
   matrix_t main, target, res;
   int i;

   if (xvector.dim != yvector.dim)
      raise_error("Dimension dismatch found");

   result.dim = 2;
   target.shape.row = 1, target.shape.col = yvector.dim;
   main = matrices_ones((shape_t) {2, xvector.dim});

   // Complete the 'main' and 'target' matrices using axis vectors.
   for (i = 0; i < xvector.dim; i++)
      main.matrix[1][i] = xvector.vector[i];
   for (i = 0; i < yvector.dim; i++)
      target.matrix[0][i] = yvector.vector[i];

   // Make some matrix operations to apply regression.
   res = matrices_scaler_mul(matrices_cross_mul(matrices_cofactors(
      matrices_cross_mul(main, matrices_transpose(main))), 
      matrices_cross_mul(main, matrices_transpose(target))), 0.02);

   result.vector[0] = res.matrix[0][0], result.vector[1] = res.matrix[1][0];

   return result;
}

/**
 * Calculate the area of triangle using determinant where 
 * corners of that triangle are in `xvector` and `yvector`.
 */
double apps_area(vector_t xvector, vector_t yvector)
{
   matrix_t main;
   int i;
   double result;

   if ((xvector.dim != yvector.dim) || (xvector.dim != 3) ||
       (yvector.dim != 3))
      raise_error("Dimension dismatch found");

   main = matrices_ones((shape_t) {3, 3});

   for (i = 0; i < xvector.dim; i++) {
      main.matrix[0][i] = xvector.vector[i];
      main.matrix[1][i] = yvector.vector[i];
   }

   result = matrices_det(matrices_transpose(main)) / 2.0;

   return (result < 0) ? (-1.0 * result) : result;
}

/**
 * Calculate the volume of tetrahedron using determinant where corners
 * of that tetrahedron are in `xvector`, `yvector` and `zvector.`
 */
double apps_volume(vector_t xvector, vector_t yvector, vector_t zvector)
{
   matrix_t main;
   int i;
   double result;

   if ((xvector.dim != yvector.dim) || (yvector.dim != zvector.dim) ||
       (xvector.dim != 4) || (yvector.dim != 4) || (zvector.dim != 4))
      raise_error("Dimension dismatch found");

   main = matrices_ones((shape_t) {4, 4});

   for (i = 0; i < xvector.dim; i++) {
      main.matrix[0][i] = xvector.vector[i];
      main.matrix[1][i] = yvector.vector[i];
      main.matrix[2][i] = zvector.vector[i];
   }

   result = matrices_det(matrices_transpose(main)) / 6.0;

   return (result < 0) ? (-1.0 * result) : result;
}
