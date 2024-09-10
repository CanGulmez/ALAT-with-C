/* Crypt the message */

#include "../source/utils.h"

void main(int argc, char *argv[])
{
   str_t message = "Today is bad, tomorrow will be worse...";

   // Crypt that 'message' using an encoder matrix.
   shape_t shape = {7, 7};
   matrix_t encoder = matrices_randint(-10, 10, shape);

   matrix_t encoded = crypts_encode(message, encoder);

   // Display the 'encoded' matrix.
   for (int i = 0; i < encoded.shape.row; i++) {
      for (int j = 0; j < encoded.shape.col; j++) {
         printf("%f ", encoded.matrix[i][j]);
      }
      printf("\n");
   }

   // Convert back 'encoded' message to original message.
   str_t orig_msg = crypts_to_message(encoded, encoder);

   printf("%s\n", orig_msg);

   exit(EXIT_SUCCESS);
}