/*  Some applications in ALAT (Advanced Linear Algebra Toolkit)  */

#include "../include/apps.h"

/* --------------------------------------------------------------- */
/* ----------------------- Helper Functions  --------------------- */
/* --------------------------------------------------------------- */

/** @brief Display the 'points_t' object contents.
 *  @param points 'points_t' object that will be displayed.
 *  @return `void` object. 
 */
void __display_points__(points_t points) {
   // Display the lenght of 'points_t' object.
   printf("Lenght: %d\n", points.len);
   // Display the axis points of 'points_t' object.
   printf("Points: ");
   for (int i=0; i<points.len; i++)
      printf("%f ", points.points[i]);
   printf("\n");
}

/* --------------------------------------------------------------- */
/* ------------------------ Main Functions ----------------------- */
/* --------------------------------------------------------------- */

/** @brief  Apply the polynomial curve fitting technique. 
 *  @param  x_points x axis points list.
 *  @param  y_points y axis points list.
 *  @return `points_t` object.
 */
points_t poly_curve_fitting(points_t x_points, points_t y_points){
   // Check that there is any dimension incompability.
   assert (x_points.len == y_points.len);
   // Indicate the local variablea and its default settings.
   matrix_t xmatrix, ymatrix, rmatrix;
   points_t result;
   xmatrix.row = x_points.len, xmatrix.col = x_points.len;
   ymatrix.row = 1, ymatrix.col = y_points.len;
   result.len = x_points.len;
   // Generate the 'xmatrix' by processing 'x_points'.
   for (int i=0; i<x_points.len; i++) {
      int index = 0;
      while (true) {
         double value = pow(x_points.points[i], index);
         xmatrix.matrix[i][index] = value, index ++;
         // Break up the loop.
         if (index == x_points.len)
            break;
   }}
   // Fill in the 'ymatrix' matrix with 'y_points'.
   for (int i=0; i<y_points.len; i++)
      ymatrix.matrix[0][i] = y_points.points[i];
   // Make the some matrix operations.
   rmatrix = cross_mul(inverse(xmatrix), transpose(ymatrix));
   // Convert the 'mul' matrix into points_t object.
   for (int i=0; i<rmatrix.row; i++)
      result.points[i] = rmatrix.matrix[i][0];

   return result;
}

/** @brief Apply the least squares regression technique. 
 *  @param  x_points x axis points list.
 *  @param  y_points y axis points list.
 *  @return `points_t` object.
 */
points_t least_squares_reg(points_t x_points, points_t y_points){
   // Check that the lenght of both axis points are same or not.
   assert (x_points.len == y_points.len);
   // Indicate the local variable/s and set its default contents.
   matrix_t matrix, target, rmatrix;
   points_t result;
   target.row = 1, target.col = y_points.len, result.len = 2;
   // Create a special ones matrix and then
   matrix = ones(2, x_points.len);
   // relapace the second row with x axis points.
   for (int i=0; i<x_points.len; i++)
      matrix.matrix[1][i] = x_points.points[i];
   // Create the 'target' matrix.
   for (int i=0; i<y_points.len; i++)
      target.matrix[0][i] = y_points.points[i];
   // Make some matrix operations onto thoose two matrices.
   rmatrix = scaler_mul(0.02, cross_mul(cofactors(
             cross_mul(matrix, transpose(matrix))), 
             cross_mul(matrix, transpose(target))));
   // Fill in the 'result' points with 'rmatrix' matrix.
   result.points[0] = rmatrix.matrix[0][0];
   result.points[1] = rmatrix.matrix[1][0];

   return result;
}

/** @brief   Calculate the area of triangle using determinant.
 *  @param   x_points x axis points list.
 *  @param   y_points y axis points list.
 *  @return  `double` object. 
 */ 
double area(points_t x_points, points_t y_points) {
   // Axis points list must contain the three corners.
   assert ((x_points.len == y_points.len) && (x_points.len == 3));
   // Create a ones matrix.
   matrix_t matrix = ones(3, 3);
   // Fill the ones matrix with the axis points.
   for (int i=0; i<x_points.len; i++)
      matrix.matrix[0][i] = x_points.points[i], 
      matrix.matrix[1][i] = y_points.points[i];
   // Calculate the area of triangle.
   double result = det(transpose(matrix)) / 2;

   return (result < 0) ? (-1.0 * result) : result;
}

/** @brief   Calculate the volume of tetrahedron using determinant.
 *  @param   x_points x axis points list.
 *  @param   y_points y axis points list.
 *  @param   z_points z axis points list.
 *  @return  `double` object. 
 */ 
double volume(points_t x_points, points_t y_points, points_t z_points){
   // Check that each axis points have the same four corners.
   assert ((x_points.len == y_points.len) &&
           (x_points.len == z_points.len) &&
           (x_points.len == 4));
   // Create a ones matrix.
   matrix_t matrix = ones(4, 4);
   // Fill in the ones matrix with the axis points.
   for (int i=0; i<x_points.len; i++)
      matrix.matrix[0][i] = x_points.points[i], 
      matrix.matrix[1][i] = y_points.points[i], 
      matrix.matrix[2][i] = z_points.points[i];
   // Calculate the volume of tetrahedron.
   double result = det(transpose(matrix)) / 6;

   return (result < 0) ? (-1.0 * result) : result;
}
