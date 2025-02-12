/* Checking Matrix */

#include "../src/alat.h"

void main(int argc, char *argv[])
{
   int i, j;
   
   shape_t shape = {4, 4};
   matrix_t fmatrix = alat_matrix_random(shape);
   matrix_t smatrix = alat_matrix_random(shape);

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

   printf("Is 'fmatrix' square: %d\n", alat_matrix_issquare(fmatrix));
   printf("Is 'fmatrix' homogen: %d\n", alat_matrix_ishomogen(fmatrix));
   printf("Is 'fmatrix' zeros: %d\n", alat_matrix_iszeros(fmatrix));
   printf("Is 'fmatrix' ones: %d\n", alat_matrix_isones(fmatrix));
   printf("Is 'fmatrix' arbitrary: %d\n", alat_matrix_isarbitrary(fmatrix, 0.8));
   printf("Is 'fmatrix' lower triangle: %d\n", alat_matrix_islowertri(fmatrix));
   printf("Is 'fmatrix' upper triangle: %d\n", alat_matrix_isuppertri(fmatrix));
   printf("Is 'fmatrix' diagonal: %d\n", alat_matrix_isdiagonal(fmatrix));
   printf("Is 'fmatrix' symmetric: %d\n", alat_matrix_issymmetric(fmatrix));
   printf("Is 'fmatrix' and 'smatrix' eqaul: %d\n", alat_matrix_isequal(fmatrix, smatrix));
   printf("Is 'fmatrix' triangle: %d\n", alat_matrix_istriangle(fmatrix));
   printf("Is 'fmatrix' invertible: %d\n", alat_matrix_isinvertible(fmatrix));

   exit(EXIT_SUCCESS);
}