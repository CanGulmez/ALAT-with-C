/* Cryptography operations in ALAT (Advanced Linear Algebra Toolkit) */

#include "./alat.h"

/**
 * Convert the `message` to square matrix which has `shape`.
 */
matrix_t alat_crypt_to_matrix(msg_t message, shape_t shape)
{
   int i, j, index;
   matrix_t result;

   assert_shape(shape);
   
   index = 0; i = 0; j = 0;
   result = alat_matrix_arbitrary(-1.0, shape);

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
matrix_t alat_crypt_encode(msg_t message, matrix_t encoder)
{
   assert (alat_matrix_isinvertible(encoder));

   return alat_matrix_cross_mul(alat_crypt_to_matrix(message, 
      encoder.shape), encoder);
}

/**
 * Decode the `message` using `encoder`. Note that `encoder`
 * must be invertible.
 */
matrix_t alat_crypt_decode(matrix_t encoded, matrix_t encoder)
{
   return alat_matrix_cross_mul(encoded, alat_matrix_inverse(encoder));
}

/**
 * Convert the `encoded` matrix back to original message using 
 * `encoder`. Note that `encoder` must be invertible.
 */
msg_t alat_crypt_to_message(matrix_t encoded, matrix_t encoder)
{
   int index, i, j, lenght;
   matrix_t decoded;
   msg_t message;

   assert_matrix(encoded);
   assert_matrix(encoder);
   assert (alat_matrix_isinvertible(encoder));

   index = 0; lenght = 0;
   decoded = alat_crypt_decode(encoded, encoder);
 
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
 