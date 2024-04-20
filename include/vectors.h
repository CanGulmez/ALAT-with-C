/*  Vector Operations in ALAT (Advanced Linear Algebra Toolkit)  */

#ifndef VECTORS_H
#define VECTORS_H

// Standard C Libraries:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

// Global Variables:
#define LEN                   32*32

#define DEG(rad)              (rad * 180.0 / M_PI)
#define RAD(deg)              (deg * M_PI / 180.0)

// New Data Types:
typedef unsigned int dim_t;
typedef double vec_t;

// User-defined Enumerations:
typedef enum {
   false, 
   true, 
} boolean;

typedef enum {
   CARTESIAN,                 // Cartesian coordinate
   CYLINDRICAL,               // Cylindrical coordinate
   SPHERICAL,                 // Spherical coordinate
} coor_t;

typedef enum {
   DECIMAL,                   // Decimal form
   RADIANS,                   // Radians form
   DEGREES,                   // Degrees form
} form_t;
 
// User-defined Structure:
typedef struct {
   dim_t dim;                 // Dimension of vector
   coor_t coor;               // Coordinate of vector
   vec_t vector[LEN];         // Vector itself
} vector_t;

// Helper Function Prototypes:

void __display_vector__(vector_t vector);

// Main Function Prototypes:

vector_t transform(vector_t vector, coor_t coordinate);
double lenght(vector_t vector);
boolean isequal(vector_t vector1, vector_t vector2);
boolean iszeros(vector_t vector);
vector_t unit(vector_t vector);
vector_t add(vector_t vector1, vector_t vector2);
vector_t scaler_mul(double scaler, vector_t vector);
vector_t cross_mul(vector_t vector1, vector_t vector2);
double distance(vector_t vector1, vector_t vector2);
double dot_mul(vector_t vector1, vector_t vector2);
boolean iscs(vector_t vector1, vector_t vector2);
boolean istriangle(vector_t vector1, vector_t vector2);
boolean ispythag(vector_t vector1, vector_t vector2);
double angle(form_t form, vector_t vector1, vector_t vector2);
boolean issteep(vector_t vector1, vector_t vector2);
boolean isparallel(vector_t vector1, vector_t vector2);

#endif /* VECTORS_H */
