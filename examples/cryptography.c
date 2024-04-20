/* Cryptography examples in ALAT (Advanced Linear Algebra Toolkit) */

#include "../include/crypts.h"

void main(int argc, char *argv) {

   // Indicate a message to encode it.
   str_t message = "Beleif creates the actual facts.";

   // Convert the message into a matrix.
   matrix_t matrix = to_matrix(message);

   // Encode the message using encoder matrix. Note that encoder
   // matrix must be invertible and have same dimension of matrix.
   matrix_t encoder = { .row = 6, 
                        .col = 6, 
                        .matrix = {{1, 0, 1, 4, 0, 1}, 
                                   {0, 0, 2, -2, 0, 0}, 
                                   {5, 1, 0, 2, 0, 3}, 
                                   {1, 2, 1, 0, 2, 0}, 
                                   {2, 2, 0, -1, 5, 8}, 
                                   {0, -3, 1, 8, 3, 0}} 
                      };

   matrix_t encoded = encode(message, encoder);

   // Decode the encoded matrix into original matrix.
   matrix_t decoded = decode(encoded, encoder);

   // Decode the encoded matrix into message.
   str_t msg = to_message(encoded, encoder);

   __display_matrix__(matrix);
   printf("\n");

   __display_matrix__(encoded);
   printf("\n");

   __display_matrix__(decoded);
   printf("\n");

   printf("Encoded message: %s\n", msg);
}