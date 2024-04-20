/* Cryptography operations in ALAT (Advanced Linear Algebra Toolkit) */

#ifndef CRYPTS_H
#define CRYPTS_H

// My libraries:
#include "../include/matrices.h"

// Consistent characters:
#define CHARACTERS "\
0123456789\
ABCDEFGHIJKLMNOPQRSTUVWXYZ\
abcdefghijklmnopqrstuvwxyz\
é!'^+$%&/\\(){}[]=*-?-_~;,`.: <>|\"@\
"  

// New data types:
typedef char * str_t;

// Function Prototypes:

matrix_t to_matrix(str_t message);
matrix_t encode(str_t message, matrix_t encoder);
matrix_t decode(matrix_t encoded, matrix_t encoder);
str_t to_message(matrix_t encoded, matrix_t encoder);

#endif /* CRYPTS_H */
