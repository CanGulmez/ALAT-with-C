/* Complex operations in ALAT (Advanced Linear Algebra Toolkit) */

#ifndef COMPLEXES_H
#define COMPLEXES_H

// Standard C Libraries:
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

// Global Constants:
#define DEG(rad)              (rad * 180.0 / M_PI)
#define RAD(deg)              (deg * M_PI / 180.0)

// New type types:
typedef double com_t;
 
// User-defined Enumerations:
typedef enum {
   false, 
   true, 
} boolean;

typedef enum {
   CARTESIAN, 
   POLAR, 
} form_t;

// typedef struct {
//    form_t form;         // form of complex number
//    part_t part_1;       // x or r
//    part_t part_2;       // y or tetha 
// } complex_t;
 
typedef struct {
   form_t form;      // form of complex number (CARTESIAN or POLAR)
   com_t complex[2]; // complex number components
} complex_t;

// Helper Function Prototypes:

void __display_complex__(complex_t complex);

// Main Function Prototypes:

complex_t transform(complex_t complex, form_t form);
complex_t add(complex_t complex1, complex_t complex2);
complex_t subtract(complex_t complex1, complex_t complex2);
complex_t multiply(complex_t complex1, complex_t complex2);
complex_t divide(complex_t complex1, complex_t complex2);
complex_t conjugate(complex_t complex);
complex_t power(complex_t complex, int n);
complex_t root(complex_t complex, int n);
boolean isequal(complex_t complex1, complex_t complex2);
boolean istriangle(complex_t complex1, complex_t complex2);

#endif /* COMPLEXES_H */
 