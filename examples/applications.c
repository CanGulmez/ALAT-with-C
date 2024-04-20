/* Application examples in ALAT (Advanced Linear Algebra Toolkit) */

#include "../include/apps.h"

void main(int argc, char *argv[]) {

   // Indicate the some x any y axis points.
   points_t x_points = { .len = 5,        // lenght of x axis points
                         .points = {7, 1, 2, -5, -1}, // points
                       };
   points_t y_points = { .len = 5,        // lenght of y axis points
                         .points = {1, 4, -7, -7, 2}, // points
                       };

   // Apply polynomial curve fitting.
   // Result points of polynomial curve fitting:
   // f(x) = 7.003472 + 1.215625x - 4.112153x^2 -
   //        0.215625x^3 + 0.108681x^4
   points_t res1 = poly_curve_fitting(x_points, y_points);

   // Apply least squares regression.
   // Result points of least squares regression:
   // f(x) = -13.600000 + 3.560000x 
   points_t res2 = least_squares_reg(x_points, y_points);

   __display_points__(res1); 
   printf("\n");

   __display_points__(res2);
   printf("\n");

   // Calculate the area of triangle using determinant.
   // Both points_t object must include x and y corner points.
   points_t x_tri = { .len = 3,            // corner of triangle
                      .points = {1, 2, 4}, // x corner points
                    };
   points_t y_tri = { .len = 3,            // corner of triangle
                      .points = {0, 2, 3}  // y corner points
                    };

   double res3 = area(x_tri, y_tri);

   printf("Area of triangle: %f\n", res3);

   // Calculate the volume of tetrahedron using determinant:
   // Both points_t objects must include x, y and z corner points.
   points_t x_tetra = { .len = 4,               // corner of tetrahedron
                        .points = {0, 4, 3, 2}, // x corner points
                      };
   points_t y_tetra = { .len = 4,               // corner of tetrahedron
                        .points = {4, 0, 5, 2}, // y corner points
                      };
   points_t z_tetra = { .len = 4,               // corner of tetrahedron
                        .points = {1, 0, 2, 5}, // z corner points
                      };
                     
   double res4 = volume(x_tetra, y_tetra, z_tetra);

   printf("Volume of tetrahedron: %f\n", res4);
}
