/*   Matrix Operations in ALAT (Advanced Linear Algebra Toolkit)   */

#include "../include/matrices.h"

/* --------------------------------------------------------------- */
/* ----------------------- Helper Functions  --------------------- */
/* --------------------------------------------------------------- */

/** @brief Display the 'matrix' matrix with rows and columns.  
 *  @param matrix Matrix that will be displayed.
 *  @return `void` object. 
*/
void __display_matrix__(matrix_t matrix) {
   // Display row and column informations.
   printf("Shape (row, col): (%d,%d)\n", 
          matrix.row, matrix.col);
   // Display the all elements of 'matrix' matrix.
   for (int i=0; i<matrix.row; i++) {
      for (int j=0; j<matrix.col; j++)
         printf("%f ", matrix.matrix[i][j]);
      printf("\r\n");
   }
}

/** @brief  Convert 'matrix' matrix to array.
 *  @param  matrix Matrix that will be converted to array. 
 *  @return `array_t` object.
 */
array_t __to_array__(matrix_t matrix) {
   // Indicate local variable/s.
   array_t result;
   int index = 0;
   // Iterate the all elements of 'matrix' matrix 
   // and then append them onto 'result' array.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++)
         result.array[index] = matrix.matrix[i][j], 
         index ++;
   // Save the lenght of new 'result' array.
   result.len = index;

   return result;
}

/** @brief  Convert 'array' array to matrix.
 *  @param  array Array that will be converted to matrix.
 *  @param  row Row info of new matrix that will be created. 
 *  @param  col Column info of new matrix that will be created.
 *  @return `matrix_t` object.
 */
matrix_t __to_matrix__(array_t array, row_t row, col_t col) {
   // Check that lenght of 'array' array and dimension
   // of new matrix that will be created.
   assert (array.len == row * col);
   // Indicate the local variable/s.
   matrix_t result;
   int index = 0;
   // Save the row and column info of 'result' matrix.
   result.row = row, result.col = col;
   // Iterate the all elements of 'array' array and then 
   // append them onto new matrix that will be created.
   for (int i=0; i<row; i++)
      for (int j=0; j<col; j++)
         result.matrix[i][j] = array.array[index], 
         index ++;

   return result;
}

/** @brief Copy the content of 'matrix' matrix to new matrix. 
 *  @param matrix Matrix that will be copied.
 *  @return `matrix_t` object.
 */
matrix_t __copy_matrix__(matrix_t matrix) {
   // Indicated the local variable/s.
   matrix_t result;
   // Copy the 'matrix' matrix onto 'result' matrix.
   memcpy(&result, &matrix, sizeof(matrix));

   return result;
}

/** @brief Delete the 'row' row from 'matrix' matrix.
 *  @param row Row that will be deleted.
 *  @param matrix Matrix that will delete 'row' row.
 *  @return `matrix_t` object.
 */
matrix_t __delete_row__(int row, matrix_t matrix) {
   // Indicate the local variable/s.
   matrix_t result;
   int index = 0;
   // Save the row and column information onto 'result' matrix.
   result.row = matrix.row - 1, result.col = matrix.col;
   // Delete the 'row' row.
   for (int i=0; i<row; i++) {
      for (int j=0; j<matrix.col; j++)
         result.matrix[index][j] = matrix.matrix[i][j];
      index ++;
   }
   for (int i=row+1; i<matrix.row; i++) {
      for (int j=0; j<matrix.col; j++)
         result.matrix[index][j] = matrix.matrix[i][j];
      index ++;
   }
   return result;
}

/** @brief Delete the 'col' column from 'matrix' matrix.
 *  @param col Column that will be deleted.
 *  @param matrix Matrix that will delete 'col' column.
 *  @return `matrix_t` object.
 */
matrix_t __delete_col__(int col, matrix_t matrix) {
   // Can be used previously defined functions to delete 
   // 'col' column from 'matrix' matrix. 
   return transpose(__delete_row__(col, transpose(matrix)));
}


/* --------------------------------------------------------------- */
/* ------------------------ Main Functions ----------------------- */
/* --------------------------------------------------------------- */

/** @brief Extract diagonal matrix of 'matrix' matrix. 
 *  @param matrix Matrix that will be extracted its diagonal.
 *  @return `matrix_t` object.
 */
matrix_t diagonal(matrix_t matrix) {
   // Check that 'matrix' matrix is square or not. 
   assert (matrix.row == matrix.col);
   // Indicate the local variable/s.
   matrix_t result;
   // Save row and column info onto 'result' matrix.
   result.row = matrix.row, result.col = matrix.col;
   // Extract the diagonal matrix from 'matrix' matrix.
   for (int i=0; i<matrix.row; i++)
      result.matrix[0][i] = matrix.matrix[i][i];

   return result;
}

/** @brief Return true, if 'matrix' matrix is homogen, otherwise 
 *         return false.
 *  @param matrix Matrix that is used to check the homogen state.
 *  @return `boolean` object.
 */
boolean ishomogen(matrix_t matrix) {
   // Check the last elements of each row of 'matrix' matrix.
   for (int i=0; i<matrix.row; i++)
      if (matrix.matrix[i][matrix.col-1] != 0)
         return false;

   return true;
}

/** @brief Return true, if 'matrix' matrix is zeros, otherwise 
 *         return false.
 *  @param matrix Matrix that is used to check the zeros state.
 *  @return `boolean` object.
 */
boolean iszeros(matrix_t matrix) {
   // Check the all elements of 'matrix' matrix.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++)
         if (matrix.matrix[i][j] != 0)
            return false;

   return true;
}

/** @brief Return true, if 'matrix' matrix is ones, otherwise 
 *         return false.
 *  @param matrix Matrix that is used to check the ones state.
 *  @return `boolean` object.
 */
boolean isones(matrix_t matrix) {
   // Check the all elements of 'matrix' matrix.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++)
         if (matrix.matrix[i][j] != 1)
            return false;

   return true;
}

/** @brief Return true, if 'matrix' matrix is identity, otherwise 
 *         return false.
 *  @param matrix Matrix that is used to check the identity state.
 *  @return `boolean` object.
 */
boolean isidentity(matrix_t matrix) {
   // Check the all elements of 'matrix' matrix.
   if (matrix.row == matrix.col) 
      for (int i=0; i<matrix.row; i++)
         for (int j=0; j<matrix.col; j++)
            if ((i == j && matrix.matrix[i][j] != 1) ||
                (i != j && matrix.matrix[i][j] != 0))
               return false;

   return true;
}

/** @brief Create new zeros matrix.
 *  @param row Row information of new zeros marix.
 *  @param col Column information of new zeros matrix.
 *  @return `matrix_t` object.
 */
matrix_t zeros(row_t row, col_t col) {
   // Indicate the new local variable/s.
   matrix_t result;
   // Save the row and column info onto 'result'.
   result.row = row, result.col = col;
   // Fill in the 'result' matrix with zeros.
   for (int i=0; i<result.row; i++)
      for (int j=0; j<result.col; j++)
         result.matrix[i][j] = 0.0;

   return result;
}

/** @brief Create new ones matrix.
 *  @param row Row information of new ones marix.
 *  @param col Column information of new ones matrix.
 *  @return `matrix_t` object.
 */
matrix_t ones(row_t row, col_t col) {
   // Indicate the local variables.
   matrix_t result;
   // Save the row and column info onto 'result'.
   result.row = row, result.col = col; 
   // Fill  in 'result' matrix with ones.
   for (int i=0; i<result.row; i++)
      for (int j=0; j<result.col; j++)
         result.matrix[i][j] = 1.0;

   return result;
}

/** @brief Create new identity matrix.
 *  @param row Row information of new identity marix.
 *  @param col Column information of new identity matrix.
 *  @return `matrix_t` object.
 */
matrix_t identity(row_t row, col_t col) {
   // Identity matrix must be square.
   assert (row == col);
   // Indicate the new local variable/s.
   matrix_t result;
   // Save the row and column info onto 'result'.
   result.row = row, result.col = col; 
   // Fill in 'result' matrix with ones and zeros.
   for (int i=0; i<result.row; i++)
      for (int j=0; j<result.col; j++)
         if (i == j) 
            result.matrix[i][j] = 1.0;
         else
            result.matrix[i][j] = 0.0;

   return result;
}

/** @brief Create new arbitrary matrix.
 *  @param value Value that will be appended in new matrix.
 *  @param row Row information of new arbitrary marix.
 *  @param col Column information of new arbitrary matrix.
 *  @return `matrix_t` object.
 */
matrix_t arbitrary(double value, row_t row, col_t col) {
      // Indicate new local variable/s.
   matrix_t result;
   // Save the row and column info onto 'result'.
   result.row = row, result.col = col; 
   // Fill in 'result' matrix with 'value'.
   for (int i=0; i<result.row; i++)
      for (int j=0; j<result.col; j++)
         result.matrix[i][j] = value;

   return result;
}

/** @brief Create new sequential matrix.
 *  @param start Start value of sequnetial matrix.
 *  @param end End value of sequential matrix
 *  @param row Row information of new sequential marix.
 *  @param col Column information of new sequential matrix.
 *  @return `matrix_t` object.
 */
matrix_t sequential(int start, int end, row_t row, col_t col) {
   // Indicate the local variable/s.
   matrix_t result;
   double total = start;
   // Calculate the step interval of the elements of 'result'.
   double step = (double) (end-start) / (double) (row*col-1);
   // Save the row and column info onto 'result'.
   result.row = row, result.col = col;
   // Append the sequential values onto 'result' matrix.
   for (int i=0; i<result.row; i++)
      for (int j=0; j<result.col; j++)
         result.matrix[i][j] = total, total += step;

   return result;
}
 
/** @brief Create new random-doubled matrix.
 *  @param start Start value of random-doubled matrix.
 *  @param end End value of random-doubled matrix
 *  @param row Row information of new random-doubled marix.
 *  @param col Column information of new random-doubled matrix.
 *  @return `matrix_t` object.
 */
matrix_t randouble(int start, int end, row_t row, col_t col) {
   // Check if the 'end' is bigger or equal to 'start' or not.
   assert (end >= start);
   // Change the clock's seed continualy.
   srand(time(NULL));
   // Create the result matrix and indicate its properties.
   matrix_t result;
   result.row = row, result.col = col;
   // There are three possible cases in here. Let's detect each
   // of them and write appropriate the code blocks. 
   for (int i=0; i<row; i++) {
      for (int j=0; j<col; j++) {
         // If the both 'end' and 'start' parameters are 
         // bigger than zeros.
         if (start >= 0 && end >= 0) {
            while (true) {
               double value = rand() % (end + 1);
               if (value >= start) {
                  result.matrix[i][j] = value;
                  break;
            }}}
         // If the both 'end' and 'start' parameters are
         // smaller than zero.
         else if (start < 0 && end < 0) {
            while (true) {
               double value = rand() % (-1 * start + 1);
               if (value >= -1 * end) {
                  result.matrix[i][j] = -1 * value;
                  break;
            }}}
         // If the 'start' parameter is smaller than zero
         // and 'end' parameter is bigger than zero. 
         else {
            double value1 = rand() % (end + 1);
            double value2 = rand() % (end + 1);
            if (value1 < value2)
               value1 *= -1;
            while (true) {
               if (value1 >= start) {
                  result.matrix[i][j] = value1;
                  break;
            }}}
   }}
   return result;
}

/** @brief Return true, if both matrices are same, otherwise, 
 *         return false.
 *  @param matrix1 First matrix which will be checked.
 *  @param matrix2 Second matrix which will be checked
 *  @return `boolean` object.
 */
boolean isequal(matrix_t matrix1, matrix_t matrix2) {
   // Check that dimension of both matrices are same or not.
   if (matrix1.row != matrix2.row || matrix1.col != matrix2.col)
      return false;
   // Check the all elements of matrices.
   for (int i=0; i<matrix1.row; i++)
      for (int j=0; j<matrix1.col; j++)
         if (matrix1.matrix[i][j] != matrix2.matrix[i][j])
            return false;

   return true;
}

/** @brief Find the highest value in 'matrix' matrix.
 *  @param matrix Matrix will be inspected to find it.
 *  @return `double` object.
 */
double highest(matrix_t matrix) {
   // Assign the first element of 'matrix' by default.
   double high = matrix.matrix[0][0];
   // Find the highest element of the 'matrix' matrix.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++)
         if (matrix.matrix[i][j] > high)
            high = matrix.matrix[i][j];

   return high;
}

/** @brief Find the lowest value in 'matrix' matrix.
 *  @param matrix Matrix that will be inspected to find it.
 *  @return `double` object.
 */
double lowest(matrix_t matrix) {
   // Assign the first element of 'matrix' matrix.
   double low = matrix.matrix[0][0];
   // Find the lowest element of the 'matrix' matrix.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++)
         if (matrix.matrix[i][j] < low)
            low = matrix.matrix[i][j];

   return low;
}

/** @brief Get the transpose of 'matrix' matrix.
 *  @param matrix Matrix that will be transposed.
 *  @return `matrix_t` object.
 */
matrix_t transpose(matrix_t matrix) {
   // Indicate the local variable/s.
   matrix_t result;
   // Save the row and column info onto 'result'.
   result.row = matrix.col, result.col = matrix.row;
   // Get the transpose of the 'matrix' matrix.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++)
         result.matrix[j][i] = matrix.matrix[i][j];

   return result;
}

/** @brief Aggregate the elements of 'matrix' as vertically.
 *  @param matrix Matrix that will be aggregated as vertically.
 *  @return `matrix_t` object.
 */
matrix_t agg_ver(matrix_t matrix) {
   // Indicate the local variables.
   matrix_t result;
   double total = 0.0;
   // Save the row and column info onto 'result' matrix.
   result.row = matrix.row, result.col = 1;
   // Aggregate the 'matrix' matrix as vertical.
   for (int i=0; i<matrix.row; i++) {
      for (int j=0; j<matrix.col; j++)
         total += matrix.matrix[i][j];
      result.matrix[i][0] = total, total = 0;
   }

   return result;
}

/** @brief Aggregate the elements of 'matrix' as horizontally.
 *  @param matrix Matrix that will be aggregated as horizontally.
 *  @return `matrix_t` object.
 */
matrix_t agg_hor(matrix_t matrix) {
   // Indicate the local variable/s.
   matrix_t result;
   // To aggregate the 'matrix' matrix as horizontally, 
   // can be used previously defined functions.
   return transpose(agg_ver(transpose(matrix)));
}

/** @brief Return true, if the 'matrix' matrix is lower 
 *         triangular, otherwise, return false.
 *  @param matrix Matrix that will be checked.
 *  @return `boolean` object.
 */
boolean islowertri(matrix_t matrix) {
   // Check the dimension of 'matrix' matrix.
   if (matrix.row != matrix.col)
      return false;
   // Indicate the local variable/s.
   double ltri[(int) (matrix.row * matrix.col / 2)];
   int index = 0;
   // Collect the upper side of 'matrix' matrix.
   for (int i=0; i<matrix.row-1; i++)
      for (int j=i+1; j<matrix.col; j++)
         ltri[index] = matrix.matrix[i][j], 
         index ++;
   // Check if the elements of 'matrix' are zeros or not.
   for (int i=0; i<index; i++)
      if (ltri[i] != 0.0) 
         return false;

   return true; 
}

/** @brief Return true, if the 'matrix' matrix is upper 
 *         triangular, otherwise, return false.
 *  @param matrix Matrix that will be checked.
 *  @return `boolean` object.
 */
boolean isuppertri(matrix_t matrix) {
   // Can be used the above functions to it.
   return true ? islowertri(transpose(matrix)) : false;
}

/** @brief Return true, if the 'matrix' matrix is upper 
 *         triangular or lower triangular, otherwise, 
 *         return false.
 *  @param matrix Matrix that will be checked.
 *  @return `boolean` object.
 */
boolean istriangle(matrix_t matrix) {
   // To checks if the 'matrix' matrix is triangular matrix,
   // and then can be used previously defined two functions. 
   return true ? (islowertri(matrix) || isuppertri(matrix)) :
          false;
}

/** @brief Calculate the mean of 'matrix' matrix.
 *  @param matrix Matrix that will be calculated.
 *  @return `double` object.
 */
double mean(matrix_t matrix) {
   // Indicate the local variable/s.
   double total = 0.0;
   // Sum the all elements of 'matrix' matrix.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++)
         total += matrix.matrix[i][j];

   return total / (matrix.row * matrix.col);
}

/** @brief Sort the elements of 'matrix' matrix ascendingly.
 *  @param matrix Matrix that will be sorted ascendingly.
 *  @return `matrix_t` object.
 */
matrix_t sort_asc(matrix_t matrix) {
   // Indicate the local variable/s.
   int temp = matrix.matrix[0][0];
   array_t array = __to_array__(matrix);
   // Iterate and compares the all elements of 'matrix'.
   for (int i=0; i<array.len; i++)
      for (int j=0; j<array.len; j++)
         if (array.array[i] < array.array[j])
            temp = array.array[i], 
            array.array[i] = array.array[j], 
            array.array[j] = temp;

   return __to_matrix__(array, matrix.row, matrix.col);
}

/** @brief Sort the elements of 'matrix' matrix descendingly.
 *  @param matrix Matrix that will be sorted descendingly.
 *  @return `matrix_t` object.
 */
matrix_t sort_des(matrix_t matrix) {
   // Indicate the local variable/s.
   int temp = matrix.matrix[0][0];
   array_t array = __to_array__(matrix);
   // Iterate and compares the all elements of 'matrix'.
   for (int i=0; i<array.len; i++)
      for (int j=0; j<array.len; j++)
         if (array.array[i] > array.array[j])
            temp = array.array[i], 
            array.array[i] = array.array[j], 
            array.array[j] = temp;

   return __to_matrix__(array, matrix.row, matrix.col);
}

/** @brief Calculate standard deviation of 'matrix' matrix.
 *  @param matrix Matrix that will be calculated to it.
 *  @return `double` object.
 */
double stddev(matrix_t matrix) {
   // Indicate the local variable/s.
   double m = mean(matrix);
   double p = 0;
   double diff = 0;
   // Calculate the standard deviation of 'matrix'.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++) {
         diff = m - matrix.matrix[i][j];
         if (diff < 0)
            p += pow(-1 * diff, 2);
         else
            p += pow(diff, 2);
      }
   // Get the square root of result, and then return it.
   return sqrt(p / (matrix.row * matrix.col));
}

/** @brief Calculate the median element of 'matrix' matrix.
 *  @param matrix Matrix that will be calculated to it.
 *  @return `double` object.
 */
double median(matrix_t matrix) {
   // Sort the all elements of 'matrix' matrix.
   matrix_t smatrix = sort_des(matrix);
   // COnvert the sorted 'smatrix' matrix into array.
   array_t sarray = __to_array__(smatrix);
   // And then caluclates the median element.
   if (sarray.len % 2 == 1)
      return sarray.array[(int) sarray.len / 2];
   else
      return (sarray.array[(int) (sarray.len / 2) - 1] + 
              sarray.array[(int) (sarray.len / 2)]) / 2;
}

/** @brief Shuffle the element of 'matrix' matrix.
 *  @param matrix Matrix that will be shuffled.
 *  @return `matrix_t` object.
 */
matrix_t shuffle(matrix_t matrix) {
   // Converts the 'matrix' matrix to 'array' array.
   array_t array = __to_array__(matrix);
   // Indicate the local variable/s.
   int indexes[matrix.row * matrix.col];
   int index = 0;
   matrix_t result;
   // Save the row and column info onto 'result' matrix.
   result.row = matrix.row, result.col = matrix.col;
   // Set the time's seed randomly.
   srand(time(NULL));
   // Generate the random indexes.
   while (true) {
      // Generate the random index.
      int integer = rand() % (matrix.row * matrix.col);
      int isthere = 0;
      // Each index is repeated one in the list.
      for (int i=0; i<index; i++)
         if (indexes[i] != integer)
            isthere ++;
      if (isthere == index) 
         indexes[index] = integer, index ++;
      // Breaks up the loop.
      if (index == matrix.row * matrix.col)
         break;
   }
   index = 0;
   // Fill in the 'result' matrix according to indexes.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++)
         result.matrix[i][j] = array.array[indexes[index]], 
         index ++;
   
   return result;
}

/** @brief Reshape the 'matrix' matrix according to new 'row'
 *         row and 'col' column indication.
 * @param  matrix Matrix that will be reshaped.
 * @param  row    Row information of the new matrix.
 * @param  col    Column information of the new matrix.
 * @return `matrix_t` object. 
 */
matrix_t reshape(matrix_t matrix, row_t row, col_t col) {
   // Check the is there any dimension incompatiblity.
   assert (matrix.row * matrix.col == row * col);
   // Reshape the 'matrix' matrix.
   return __to_matrix__(__to_array__(matrix), row, col); 
}

/** @brief Concatenate the 'matrix1' matrix and 'matrix2' 
 *         matrix as horizontal. 
 *  @param matrix1 First matrix that will be concatenated.
 *  @param matrix2 Second matrix that will be concatenated.
 *  @return `matrix_t` object.
 */
matrix_t concat_hor(matrix_t matrix1, matrix_t matrix2) {
   // Check that is there any dimension incompatiblity.
   assert (matrix1.col == matrix2.col);
   // Indicate the local variable/s.
   matrix_t result;
   // Save the row and column informations.
   result.row = matrix1.row + matrix2.row; 
   result.col = matrix1.col;
   // Concatenate the matrices.
   for (int i=0; i<matrix1.row; i++)
      for (int j=0; j<matrix1.col; j++)
         result.matrix[i][j] = matrix1.matrix[i][j];
   for (int i=0; i<matrix2.row; i++)
      for (int j=0; j<matrix2.col; j++)
         result.matrix[i+matrix1.row][j] = matrix2.matrix[i][j];

   return result; 
}

/** @brief Concatenate the 'matrix1' matrix and 'matrix2'
 *         matrix as vertical. 
 *  @param matrix1 First matrix that will be concatenated.
 *  @param matrix2 Second matrix that will be concatenated.
 *  @return `matrix_t` object.
 */
matrix_t concat_ver(matrix_t matrix1, matrix_t matrix2) {
   // Check that is there any dimension incompatiblity.
   assert (matrix1.row == matrix2.row);
   // Indicate the local variable/s.
   matrix_t result;
   // Save the row and column informations.
   result.row = matrix1.row; 
   result.col = matrix1.col + matrix2.col;
   // Concatenate the matrices.
   for (int i=0; i<matrix1.row; i++)
      for (int j=0; j<matrix1.col; j++)
         result.matrix[i][j] = matrix1.matrix[i][j];
   for (int i=0; i<matrix2.row; i++)
      for (int j=0; j<matrix2.col; j++)
         result.matrix[i][j+matrix1.col] = matrix2.matrix[i][j];

   return result; 
}

/** @brief Add the 'matrix1' matrix and 'matrix2' matrix. 
 *  @param matrix1 First matrix that will be added.
 *  @param matrix2 Second matrix that will be added.
 *  @return `matrix_t` object.
 */
matrix_t add(matrix_t matrix1, matrix_t matrix2) {
   // Check that is there any dimension incompatiblity.
   assert (matrix1.row == matrix2.row);
   assert (matrix1.col == matrix2.col);
   // Indicate the local variable/s.
   matrix_t result;
   // Save the row and column informations.
   result.row = matrix1.row; 
   result.col = matrix1.col;
   // Add the matrices.
   for (int i=0; i<matrix1.row; i++)
      for (int j=0; j<matrix1.col; j++)
         result.matrix[i][j] = matrix1.matrix[i][j]
                             + matrix2.matrix[i][j];
   return result; 
}

/** @brief Subtract the 'matrix2' matrix from 'matrix1' matrix. 
 *  @param matrix1 First matrix that will be subtracted.
 *  @param matrix2 Second matrix that will be subtracted.
 *  @return `matrix_t` object.
 */
matrix_t subtract(matrix_t matrix1, matrix_t matrix2) {
   // Check that is there any dimension incompatiblity.
   assert (matrix1.row == matrix2.row);
   assert (matrix1.col == matrix2.col);
   // Indicate the local variable/s.
   matrix_t result;
   // Save the row and column informations.
   result.row = matrix1.row; 
   result.col = matrix1.col;
   // Subtract the matrices.
   for (int i=0; i<matrix1.row; i++)
      for (int j=0; j<matrix1.col; j++)
         result.matrix[i][j] = matrix1.matrix[i][j]
                             - matrix2.matrix[i][j];
   return result; 
}

/** @brief Multiply elements of 'matrix' matrix with 'scaler' scaler.
 *  @param scaler Scaler value that's multiplied with 'matrix' matrix.
 *  @param matrix Matrix that will be multiplied with 'scaler' scaler.
 *  @return `matrix_t` object.
 */
matrix_t scaler_mul(double scaler, matrix_t matrix) {
   // Indicate the local variable/s.
   matrix_t result;
   // Save the row and column informations.
   result.row = matrix.row, result.col = matrix.col;
   // Multiply the 'matrix' with 'scaler'.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++)
         result.matrix[i][j] = matrix.matrix[i][j] * scaler;

   return result;
}

/** @brief Multiply the 'matrix1' matrix and 'matrix2' matrix 
 *         as dot.
 *  @param matrix1 First matrix that will be multiplied.
 *  @param matrix2 First matrix that will be multiplied.
 *  @return `matrix_t` object.
 */
matrix_t dot_mul(matrix_t matrix1, matrix_t matrix2) {
   // Check that is there any dimension incompatibility.
   assert (matrix1.row == matrix2.row);
   assert (matrix2.col == matrix2.col);
   // Indicate the local variable/s.
   matrix_t result;
   // Save the row and column informations.
   result.row = matrix1.row, result.col = matrix1.col;
   // Multiply the 'matrix1' and 'matrix2'.
   for (int i=0; i<matrix1.row; i++)
      for (int j=0; j<matrix1.col; j++)
         result.matrix[i][j] = matrix1.matrix[i][j]
                             * matrix2.matrix[i][j];
   return result;
}
 
/** @brief Multiply the 'matrix1' matrix and 'matrix2' matrix 
 *         as cross.
 *  @param matrix1 First matrix that will be multiplied.
 *  @param matrix2 First matrix that will be multiplied.
 *  @return `matrix_t` object.
 */
matrix_t cross_mul(matrix_t matrix1, matrix_t matrix2) {
   // Check that is there any dimension incompatibility.
   assert (matrix1.col == matrix2.row);
   // Get the transpose of 'matrix2'.
   matrix_t tmatrix2 = transpose(matrix2);
   // Indicate the local variable/s.
   matrix_t result;
   double total = 0;
   int start = 0;
   int index = matrix1.col;
   double array[matrix1.row * matrix2.col];
   // Save the row and column informations.
   result.row = matrix1.row, result.col = matrix2.col;
   // Multiply the 'matrix1' and 'matrix2' as cross.
   for (int i=0; i<matrix1.row; i++)
      for (int j=0; j<matrix2.col; j++)
         for (int k=0; k<matrix2.row; k++) {
            double value = matrix1.matrix[i][k] 
                         * tmatrix2.matrix[j][k];
            total += value;
            index --;
            if (index == 0) 
               array[start] = total, total = 0, 
               index = matrix1.col, start ++;
         }
   // Fill the 'result' matrix.
   for (int i=0; i<result.row; i++)
      for (int j=0; j<result.col; j++)
         result.matrix[i][j] = array[(int) total], total ++;
   
   return result;
}

/** @brief Divide the 'matrix' matrix by 'scaler' scaler.
 *  @param scaler Scaler value that will divide 'matrix' matrix.
 *  @param matrix Matrix that will be divided by 'scaler' scaler.
 *  @return `matrix_t` object.
 */
matrix_t scaler_div(double scaler, matrix_t matrix) {
   // Indicate the local variable/s.
   matrix_t result;
   // Save the row and column informations.
   result.row = matrix.row, result.col = matrix.col;
   // Multiply the 'matrix' with 'scaler'.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++)
         result.matrix[i][j] = matrix.matrix[i][j] / scaler;

   return result;
}

/** @brief Divide the 'matrix2' matrix by 'matrix1' matrix as dot.
 *  @param matrix1 First matrix that will divide 'matrix2' matrix.
 *  @param matrix2 Second matrix that will be divided by 'matrix1'.
 *  @return `matrix_t` object.
 */
matrix_t dot_div(matrix_t matrix1, matrix_t matrix2) {
   // Check that is there any dimension incompatibility.
   assert (matrix1.row == matrix2.row);
   assert (matrix2.col == matrix2.col);
   // Indicate the local variable/s.
   matrix_t result;
   // Save the row and column informations.
   result.row = matrix1.row, result.col = matrix1.col;
   // Multiply the 'matrix1' and 'matrix2'.
   for (int i=0; i<matrix1.row; i++)
      for (int j=0; j<matrix1.col; j++)
         result.matrix[i][j] = matrix1.matrix[i][j]
                             / matrix2.matrix[i][j];
   return result;
}

/** @brief Calculate the determinant of 'matrix' matrix.
 *  @param matrix Matrix that will be calculated its determinant.
 *  @return `double` object.
 */
double det(matrix_t matrix) {
   // Check that 'matrix' matrix is square or not.
   assert (matrix.col == matrix.row);
   // Calculate the determinant of 1x1 matrix.
   if (matrix.row == 1)
      return matrix.matrix[0][0];
   // Calculate the determinant of 2x2 matrix.
   if (matrix.row == 2)
      return (matrix.matrix[0][0] * matrix.matrix[1][1]) - 
             (matrix.matrix[0][1] * matrix.matrix[1][0]);
   // Calculate the determinant of 3x3 and more matrices. The main 
   // strategy is to convert 'matrix' matrix into uppertriangular 
   // matrix. So, in this way, can be calculatedvdeterminant of 
   // 'matrix' matrix by multipying main diagonal.
   if (matrix.row >= 3) {
      // Indicate some local variables.
      int k = 0;
      array_t array;
      int switching = 1;
      int nonzero = 0;
      // Step by step, generate the upper triangular matrix.
      while (true) {
         for (int i=1+k; i<matrix.row; i++) {
            // Generate the sub-matrices.
            matrix_t m1, m2;
            m1.row = 1, m1.col = matrix.col;
            m2.row = 1, m2.col = matrix.col;
            // In some cases, main diagonal may contain zeros values.
            // So, algorithm does not work correctly. To fix it, can
            // be switched the rows.
            if (matrix.matrix[k][k] == 0.0) {
               // Find the nonzero row according to 'k' variable.
               for (int j=0; j<matrix.col; j++)
                  if (matrix.matrix[j][k] != 0.0)
                     nonzero = j;
               // Switch the rows.
               for (int j=0; j<matrix.col; j++)
                  array.array[j] = matrix.matrix[k][j], 
                  matrix.matrix[k][j] = matrix.matrix[nonzero][j], 
                  matrix.matrix[nonzero][j] = array.array[j];
               // In each switching step, the result must be 
               // multiplied by -1. 
               switching *= -1;
            }
            // Calculate the coefficient value.
            double coef = -1*matrix.matrix[i][k]/matrix.matrix[k][k];
            // Fill in the submatrices.
            for (int j=0; j<matrix.col; j++)
               m1.matrix[0][j] = matrix.matrix[k][j], 
               m2.matrix[0][j] = matrix.matrix[i][j];
            // Make some matrix operations onto sub-matrices.
            matrix_t result = add(m2, scaler_mul(coef, m1));
            // Replace the related the new row and the old row.
            for (int j=0; j<matrix.col; j++)
               matrix.matrix[i][j] = result.matrix[0][j];
         }
         // Update the control variable in each iteration.
         k ++;
         // Break up the loop when its time come.
         if (k == matrix.row) 
            break;
      }
      // Calculate and return determinant of 'matrix' matrix.
      double det = 1.0;
      // Multiply the diagonal elements of 'matrix' matrix.
      for (int i=0; i<matrix.row; i++) 
         det *= matrix.matrix[i][i];
      
      return det * switching;
   }
}

/** @brief Extract the minors map of 'matrix' matrix.
 *  @param matrix Matrix that will be extracted its minors.
 *  @return `matrix_t` object.
 */
matrix_t minors(matrix_t matrix) {
   // Check that 'matrix' matrix is square or not.
   assert (matrix.row == matrix.col);
   // Indicate the local variable/s.
   matrix_t result;
   // Save the row and column information onto 'result' matrix.
   result.row = matrix.row, result.col = matrix.col;
   // Extract the minors of each sub-matrices.
   for (int i=0; i<matrix.row; i++)
      for (int j=0; j<matrix.col; j++) {
         // Copy the 'matrix' matrix.
         matrix_t copied = __copy_matrix__(matrix);
         // Delete the i. row of copied matrix.
         matrix_t parsed1 = __delete_row__(i, copied);
         // Deleted the j. column of copied matrix.
         matrix_t parsed2 = __delete_col__(j, parsed1);
         // Caluclate determinant and replace it.
         result.matrix[i][j] = det(parsed2);
      }
   return result;
}

/** @brief Extract the cofactors map of 'matrix' matrix.
 *  @param matrix Matrix that will be extracted its cofactors.
 *  @return `matrix_t` object.
 */
matrix_t cofactors(matrix_t matrix) {
   // Check that 'matrix' matrix is square or not.
   assert (matrix.row == matrix.col);
   // Can be used previously defined functions.
   matrix_t result = minors(matrix);
   // Apply the cofactor rules onto 'result' matrix.
   for (int i=0; i<result.row; i++)
      for (int j=0; j<result.col; j++)
         if ((i + j) % 2 == 1 && result.matrix[i][j] != 0.0)
            result.matrix[i][j] = -1 * result.matrix[i][j];

   return result;
}

/** @brief Return true, if the 'matrix' matrix is 
 *         invertible matrix, otherwise return false.
 *  @param matrix Matrix that will be checked.
 *  @return `boolean` object.
 */
boolean isinvertible(matrix_t matrix) {
   // Can be used previously defined functions.
   return true ? (det(matrix) != 0.0) : false;
}

/** @brief Calculate the adjoint of 'matrix' matrix.
 *  @param matrix Matrix that will be calculated.
 *  @return `matrix_t` object.
 */
matrix_t adjoint(matrix_t matrix) {
   // Can be used previously defined functions.
   return transpose(cofactors(matrix));
}

/** @brief Calculate the inverse of 'matrix' matrix.
 *  @param matrix Matrix that will be inversed.
 *  @return `matrix_t` object.
 */
matrix_t inverse(matrix_t matrix) {
   // Check that 'matrix' matrix is invertible or not.
   assert (isinvertible(matrix));
   // Can be used previosly defined function.
   return scaler_div(det(matrix), adjoint(matrix));
}

matrix_t uppertri(matrix_t matrix);
matrix_t lowertri(matrix_t matrix);
 
/** @brief Solve the linear augmented 'matrix' system. Augmented
 *         matrix means that it contains both main and target 
 *         matrices. So, column number of 'matrix' linear system
 *         must be one more than row number.
 *  @param matrix Linear augmented system that will be solved.
 *  @return `matrix_t` object.
 */
matrix_t solve(matrix_t matrix) {
   // Check that the linear 'matix' system is in augmented form.
   assert (matrix.col - matrix.row == 1);
   // Indicate the some local variable/s.
   matrix_t main, target, result;
   // Save the row and column informations.
   main.row = matrix.row, main.col = matrix.col - 1;
   target.row = matrix.row, target.col = 1;
   result.row = matrix.row, result.col = 1;
   result.row = matrix.row, result.col = matrix.col;
   // Extract the main and target matrices.
   for (int i=0; i<main.row; i++)
      for (int j=0; j<main.col; j++)
         main.matrix[i][j] = matrix.matrix[i][j];
   for (int i=0; i<target.row; i++)
      for (int j=0; j<target.col; j++)
         target.matrix[i][j] = matrix.matrix[i][matrix.col-1];
   // Check that 'main' matrix is invertible or not.
   assert (isinvertible(main));
   // Lastly, solve and return the linear augmented system.
   return cross_mul(inverse(main), target);
}
 