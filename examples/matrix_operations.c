/* Matrix Operations */

#include "../src/alat.h"

void main(int argc, char *argv[])
{
   int i, j;
   
   shape_t shape = {4, 4};
   matrix_t fmatrix = alat_matrix_random(shape);
   matrix_t smatrix = alat_matrix_random(shape);

   matrix_t add = alat_matrix_add(fmatrix, smatrix);
   matrix_t sub = alat_matrix_sub(fmatrix, smatrix);
   matrix_t scalar_mul = alat_matrix_scalar_mul(fmatrix, 2.0);
   matrix_t dot_mul = alat_matrix_dot_mul(fmatrix, smatrix);
   matrix_t cross_mul = alat_matrix_cross_mul(fmatrix, smatrix);
   matrix_t scalar_div = alat_matrix_scalar_div(smatrix, 2.0);

   printf("First matrix:\n");
   for (i = 0; i < fmatrix.shape.row; i++) {
      for (j = 0; j < fmatrix.shape.col; j++) {
         printf("%.4f  ", fmatrix.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Second matrix:\n");
   for (i = 0; i < smatrix.shape.row; i++) {
      for (j = 0; j < smatrix.shape.col; j++) {
         printf("%.4f  ", smatrix.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Addition:\n");
   for (i = 0; i < add.shape.row; i++) {
      for (j = 0; j < add.shape.col; j++) {
         printf("%.4f  ", add.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Subtraction:\n");
   for (i = 0; i < sub.shape.row; i++) {
      for (j = 0; j < sub.shape.col; j++) {
         printf("%.4f  ", sub.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Scalar multiplication:\n");
   for (i = 0; i < scalar_mul.shape.row; i++) {
      for (j = 0; j < scalar_mul.shape.col; j++) {
         printf("%.4f  ", scalar_mul.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Dot multiplication:\n");
   for (i = 0; i < dot_mul.shape.row; i++) {
      for (j = 0; j < dot_mul.shape.col; j++) {
         printf("%.4f  ", dot_mul.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Cross multiplication:\n");
   for (i = 0; i < cross_mul.shape.row; i++) {
      for (j = 0; j < cross_mul.shape.col; j++) {
         printf("%.4f  ", cross_mul.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Scalar division:\n");
   for (i = 0; i < scalar_div.shape.row; i++) {
      for (j = 0; j < scalar_div.shape.col; j++) {
         printf("%.4f  ", scalar_div.matrix[i][j]);
      }
      printf("\n");
   }
   
   exit(EXIT_SUCCESS);
}