/*  Some applications in ALAT (Advanced Linear Algebra Toolkit)  */

#ifndef APPS_H
#define APPS_H

// My Libraries:
#include "../include/matrices.h"

// New Data Types:
typedef double axis_t;

// User-defined Structure:
typedef struct {
   len_t len;            // Lenght of axis points
   axis_t points[LEN];   // Axis points itself
} points_t;

// Helper Function Prototypes:

void __display_points__(points_t points);

// Main Function Prototypes:

points_t poly_curve_fitting(points_t x_points, points_t y_points);
points_t least_squares_reg(points_t x_points, points_t y_points);
double area(points_t x_points, points_t y_points);
double volume(points_t x_points, points_t y_points, points_t z_points);

#endif /* APPS_H */
 