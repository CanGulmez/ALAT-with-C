/* Creating New Matrices */

#include "../src/alat.h"

void main(int argc, char *argv[])
{
   int i, j;

   shape_t shape = {3, 3};
   matrix_t zeros = alat_matrix_zeros(shape);
   matrix_t ones = alat_matrix_ones(shape);
   matrix_t identity = alat_matrix_identity(shape);
   matrix_t arbitrary = alat_matrix_arbitrary(2.0, shape);
   matrix_t sequential = alat_matrix_sequential(-10, 10, shape);
   matrix_t random = alat_matrix_random(shape);
   matrix_t uniform = alat_matrix_uniform(-10, 10, shape);
   matrix_t randint = alat_matrix_randint(-10, 10, shape);

   printf("Zeros matrix:\n");
   for (i = 0; i < zeros.shape.row; i++) {
      for (j = 0; j < zeros.shape.col; j++) {
         printf("%.4f  ", zeros.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Ones matrix:\n");
   for (i = 0; i < ones.shape.row; i++) {
      for (j = 0; j < ones.shape.col; j++) {
         printf("%.4f  ", ones.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Identity matrix:\n");
   for (i = 0; i < identity.shape.row; i++) {
      for (j = 0; j < identity.shape.col; j++) {
         printf("%.4f  ", identity.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Arbitrary matrix:\n");
   for (i = 0; i < arbitrary.shape.row; i++) {
      for (j = 0; j < arbitrary.shape.col; j++) {
         printf("%.4f  ", arbitrary.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Sequential matrix:\n");
   for (i = 0; i < sequential.shape.row; i++) {
      for (j = 0; j < sequential.shape.col; j++) {
         printf("%.4f  ", sequential.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Random matrix:\n");
   for (i = 0; i < random.shape.row; i++) {
      for (j = 0; j < random.shape.col; j++) {
         printf("%.4f  ", random.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Uniform matrix:\n");
   for (i = 0; i < uniform.shape.row; i++) {
      for (j = 0; j < uniform.shape.col; j++) {
         printf("%.4f  ", uniform.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Randint matrix:\n");
   for (i = 0; i < randint.shape.row; i++) {
      for (j = 0; j < randint.shape.col; j++) {
         printf("%.4f  ", randint.matrix[i][j]);
      }
      printf("\n");
   }

   exit(EXIT_SUCCESS);
}