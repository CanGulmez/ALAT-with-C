/* Cryptography operations in ALAT (Advanced Linear Algebra Toolkit) */

#include "./alat.h"

/**
 * Convert the `message` to square matrix which has `shape`.
 */
matrix_t crypts_to_matrix(str_t message, shape_t shape)
{
   matrix_t result;
   int i, j, index;

   if (shape.row != shape.col)
      alat_error("Sqaure matrix error");
   
   index = 0; i = 0; j = 0;
   result = matrices_arbitrary(-1.0, shape);

   for (index = 0; index < strlen(message); index ++) {
      result.matrix[i][j] = (double) ((int) message[index]);

      j ++;
      if (j == result.shape.col)
         i ++, j = 0;
   }

   return result;
}

/**
 * Encode the `message` using `encoder`. Note that `encoder`
 * must be invertible.
 */
matrix_t crypts_encode(str_t message, matrix_t encoder)
{
   if (!matrices_issquare(encoder))
      alat_error("Square matrix error");
   if (!matrices_isinvertible(encoder))
      alat_error("Non-invertible matrix found");

   return matrices_cross_mul(crypts_to_matrix(message, 
      encoder.shape), encoder);
}

/**
 * Decode the `message` using `encoder`. Note that `encoder`
 * must be invertible.
 */
matrix_t crypts_decode(matrix_t encoded, matrix_t encoder)
{
   if (!matrices_issquare(encoder))
      alat_error("Square matrix error");
   if (!matrices_isinvertible(encoder))
      alat_error("Non-invertible matrix found");

   return matrices_cross_mul(encoded, matrices_inverse(encoder));
}

/**
 * Convert the `encoded` matrix back to original message using 
 * `encoder`. Note that `encoder` must be invertible.
 */
str_t crypts_to_message(matrix_t encoded, matrix_t encoder)
{
   str_t message;
   matrix_t decoded;
   int index, i, j, lenght;

   if (!matrices_issquare(encoder))
      alat_error("Square matrix error");
   if (!matrices_isinvertible(encoder))
      alat_error("Non-invertible matrix found");

   index = 0; lenght = 0;
   decoded = crypts_decode(encoded, encoder);

   for (i = 0; i < decoded.shape.row; i++) 
      for (j = 0; j < decoded.shape.col; j++) 
         if ((int) (float) decoded.matrix[i][j] != -1)
            lenght ++;

   message = malloc(sizeof(char) * lenght);

   for (i = 0; i < decoded.shape.row; i++) 
      for (j = 0; j < decoded.shape.col; j++) 
         if ((int) (float) decoded.matrix[i][j] != -1) 
            message[index] = (char)(int)(float) decoded.matrix[i][j],
            index ++;

   return message;
}
