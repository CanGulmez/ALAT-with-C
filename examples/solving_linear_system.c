/* Solving Linear System */

#include "../src/alat.h"

void main(int argc, char *argv[])
{
   int i, j;

   shape_t shape = {5, 6}; // main (5x5) and target (5x1) matrices
   matrix_t equation = alat_matrix_uniform(-10, 10, shape);
   matrix_t solved = alat_matrix_solve(equation);

   printf("Linear equation:\n");
   for (i = 0; i < equation.shape.row; i++) {
      for (j = 0; j < equation.shape.col; j++) {
         printf("%.4f  ", equation.matrix[i][j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("Solving equation:\n");
   for (i = 0; i < solved.shape.row; i++) {
      for (j = 0; j < solved.shape.col; j++) {
         printf("%.4f  ", solved.matrix[i][j]);
      }
      printf("\n");
   }
   
   exit(EXIT_SUCCESS);
}