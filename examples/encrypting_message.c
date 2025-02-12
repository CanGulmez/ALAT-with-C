/* Encrypting Message */

#include "../src/alat.h"

void main(int argc, char *argv[])
{
   int i, j;

   msg_t message = "Everything will be okey...";
   shape_t shape = {6, 6};
   matrix_t encoder = alat_matrix_random(shape);

   printf("Encoder matrix:\n");

   for (i = 0; i < encoder.shape.row; i++) {
      for (j = 0; j < encoder.shape.col; j++) {
         printf("%.4f  ", encoder.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Encoding message into matrix using 'encoder':\n");

   matrix_t encoded = alat_crypt_encode(message, encoder);

   for (i = 0; i < encoded.shape.row; i++) {
      for (j = 0; j < encoded.shape.col; j++) {
         printf("%.4f  ", encoded.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Decode 'encoded' matrix back to original message:\n- ");

   msg_t original = alat_crypt_to_message(encoded, encoder);

   printf("%s\n", original);

   exit(EXIT_SUCCESS);
}
