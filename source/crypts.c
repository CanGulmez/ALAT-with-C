/* Cryptography operations in ALAT (Advanced Linear Algebra Toolkit) */

#include "../include/crypts.h"

/* --------------------------------------------------------------- */
/* ------------------------ Main Functions ----------------------- */
/* --------------------------------------------------------------- */

/** @brief Convert 'message' message to square matrix. 
 *  @param message Message that will be transformed.
 *  @return `matrix_t` object. 
 */
matrix_t to_matrix(str_t message) {
   // Indicate the local variable/s.
   int edge = 1;
   array_t array;
   matrix_t result;
   // Select the appropriate row and column number.
   while (true) 
      if (pow(edge, 2) >= strlen(message))
         break;
      else
         edge ++;
   // Chect that all characters of 'message' is in 'CHARACTERS'.
   for (int i=0; i<strlen(message); i++)
      assert (strchr(CHARACTERS, message[i]) != NULL);
   // Save the row, column and lenght values to structures.
   result.row = edge, result.col = edge, array.len = edge * edge;
   // Collect the values corresponding to characters of 'message'.
   for (int i=0; i<array.len; i++)
      if (strlen(message) > i)
         array.array[i] = (double) strlen(CHARACTERS) - 
                          strlen(strchr(CHARACTERS, message[i]));
      else
         array.array[i] = -1.0;
   
   return __to_matrix__(array, edge, edge);
}

/** @brief Encode the 'message' into square matrix using 'encoder'. 
 *         'encoder' matrix must be invertible to encode message.
 *  @param message Message that will be encoded into matrix.
 *  @param encoder Encoder matrix that will encode the message.
 *  @return `matrix_t` object.
 */
matrix_t encode(str_t message, matrix_t encoder) {
   // Convert the 'message' into regular matrix.
   matrix_t matrix = to_matrix(message);
   // Check that regular and encoder matrices has same dimensions.
   assert (matrix.row == encoder.row && matrix.col == encoder.col);
   // Check that 'encoder' matrix is invertible.
   assert (isinvertible(encoder));
   // Multiply and return the multiplied matrices as cross.
   return cross_mul(matrix, encoder);
}

/** @brief Decode the 'encoded' message using 'encoder' matrix.
 *  @param encoded Encoded message that will be decoded.
 *  @param encoder Encoder matrix that will decode the message.
 *  @return `matrix_t` object.
 */
matrix_t decode(matrix_t encoded, matrix_t encoder) {
   // Check that both matrices have same dimensions.
   assert (encoded.row == encoder.row && encoded.col == encoder.col);
   // Check that 'encoder' matrix is invertible or not.
   assert (isinvertible(encoder));
   // Decode and return the encoded message.
   return cross_mul(encoded, inverse(encoder));
}

/** @brief Convert the 'encoded' message to string using 'encoder'.
 *  @param encoded Encoded message that will be decoded.
 *  @param encoder Encoder matrix that will decode the message.
 *  @return `matrix_t` object.
 */
str_t to_message(matrix_t encoded, matrix_t encoder) {
   // Indicate the local variable/s.
   static char message[LEN];
   int index = 0;
   // Check that both matrices have same dimensions.
   assert (encoded.row == encoder.row && encoded.col == encoder.col);
   // Decode the encoded message.
   matrix_t decoded = decode(encoded, encoder);
   // Convert the encoded messsage to string.
   for (int i=0; i<decoded.row; i++)
      for (int j=0; j<decoded.col; j++) 
         if ((int) (float) decoded.matrix[i][j] != -1)
            message[index] = CHARACTERS[(int) (float) 
                              decoded.matrix[i][j]], index ++;
   return message;
}
