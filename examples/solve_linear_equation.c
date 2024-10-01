/* Solve a linear equation */

#include "../source/alat.h"

void main(int argc, char *argv[])
{
   matrix_t main = {
      .shape = {4, 4}, 
      .matrix = {
         {7, -1, 3, -2}, 
         {2, 4, 7, 8}, 
         {-9, -8, 0, 0},
         {6, 4, -7, -1}
      }
   };

   // Find the determinant of 'main' matrix. 
   printf("%f\n", matrices_det(main));

   // Create a uniform 'target' matrix that has 4x1 shape. 
   shape_t shape = {4, 1};
   matrix_t target =  matrices_uniform(-10, 10, shape);

   // Concatenate the 'main' and 'target' matrices as vertical. 
   matrix_t concatenated = matrices_concat(main, target, 1);

   // Lastly solve the linear equation. 
   matrix_t solved = matrices_solve(concatenated);

   // Display the solved linear equation results. 
   for (int i = 0; i < solved.shape.row; i++) {
      for (int j = 0; j < solved.shape.col; j++) {
         printf("%f ", solved.matrix[i][j]);
      }
      printf("\n");
   }

   exit(EXIT_SUCCESS);
}