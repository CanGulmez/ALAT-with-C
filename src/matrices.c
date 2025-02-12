/* Matrix operations for ALAT (Advanced Linear Algebra Toolkit) */

#include "./alat.h"

/**
 * Return true, if `matrix` is square, otherwise return false. 
 */
bool_t alat_matrix_issquare(matrix_t matrix) 
{
   assert_matrix(matrix);

   return (matrix.shape.row == matrix.shape.col) ? true : false;
}  

/** 
 * Return true, if `matrix` is homogen, otherwise return false. 
 */
bool_t alat_matrix_ishomogen(matrix_t matrix) 
{
   assert_matrix(matrix); 

   for (int i=0; i<matrix.shape.row; i++)
      if (matrix.matrix[i][matrix.shape.col-1] != 0)
         return false;

   return true;
}

/** 
 * Return true, if `matrix` just contains `value`s, otherwise 
 * return false. 
 */
bool_t alat_matrix_isarbitrary(matrix_t matrix, double value) 
{
   int i, j;

   assert_matrix(matrix); 

   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         if (matrix.matrix[i][j] != value)
            return false;

   return true;
}

/** 
 * Return true, if `matrix` just contains 0s, 
 * otherwise return false. 
 */
bool_t alat_matrix_iszeros(matrix_t matrix) 
{
   return (alat_matrix_isarbitrary(matrix, 0.0)) ? true : false;
}

/** 
 * Return true, if `matrix` just contains 1s, 
 * otherwise return false. 
 */
bool_t alat_matrix_isones(matrix_t matrix) 
{
   return (alat_matrix_isarbitrary(matrix, 1.0)) ? true : false;
}

/** 
 * Return true, if `matrix` is identity, otherwise 
 * return false. 
 */
bool_t alat_matrix_isidentity(matrix_t matrix)
{
   int i, j;

   assert_matrix(matrix);

   if (alat_matrix_issquare(matrix) == false)
      return false;

   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         if ((i == j && matrix.matrix[i][j] != 1.0) || 
             (i != j && matrix.matrix[i][j] != 0.0))
               return false;

   return true;
}

/** 
 * Return true, if `matrix` is upper triangle, 
 * otherwise return false. 
 */
bool_t alat_matrix_isuppertri(matrix_t matrix) 
{
   int i, j;

   assert_matrix(matrix);

   if (alat_matrix_issquare(matrix) == false)
      return false; 

   for (i = 1; i < matrix.shape.row; i++)
      for (j = 0; j < i; j++)
         if (matrix.matrix[i][j] != 0.0)
            return false;

   return true;
}

/** 
 * Return true, if `matrix` is lower triangle, 
 * otherwise return false. 
 */
bool_t alat_matrix_islowertri(matrix_t matrix)
{
   return (alat_matrix_isuppertri(
      alat_matrix_transpose(matrix))) ? true : false;
}

/** 
 * Return true, if `matrix` is upper or lower triangular, 
 * otherwise return false.
 */
bool_t alat_matrix_istriangle(matrix_t matrix)
{
   return (alat_matrix_islowertri(matrix) || 
      alat_matrix_isuppertri(matrix)) ? true : false;
}

/**
 * Return true, if `matrix` is diagonal, otherwise 
 * return false.
 */
bool_t alat_matrix_isdiagonal(matrix_t matrix)
{
   return (alat_matrix_isuppertri(matrix) && 
      alat_matrix_islowertri(matrix)) ? true : false;
}

/**
 * Return true, if `matrix` is symmetric, otherwise 
 * return false.
 */
bool_t alat_matrix_issymmetric(matrix_t matrix)
{
   return (alat_matrix_isequal(matrix, 
      alat_matrix_transpose(matrix))) ? true : false;
}

/**
 * Return true, if `fmatrix` and `smatrix` are equals, otherwise, 
 * return false.
 */
bool_t alat_matrix_isequal(matrix_t fmatrix, matrix_t smatrix)
{
   int i, j;

   assert_matrix(fmatrix);
   assert_matrix(smatrix);

   if (fmatrix.shape.row != smatrix.shape.row ||
       fmatrix.shape.col != smatrix.shape.col)
      return false;

   for (i = 0; i < fmatrix.shape.row; i++)
      for (j = 0; j < fmatrix.shape.col; j++)
         if (fmatrix.matrix[i][j] != smatrix.matrix[i][j])
            return false;

   return true;
}
 
/** 
 * Return true, if `matrix` is invertible, otherwise 
 * return false. 
 */
bool_t alat_matrix_isinvertible(matrix_t matrix)
{
   return (alat_matrix_det(matrix) != 0.0) ? true : false;
}

/** 
 * Create a new arbitrary matrix which have `shape` and 
 * filled with `value`s.
 */
matrix_t alat_matrix_arbitrary(double value, shape_t shape) 
{
   int i, j;
   matrix_t result;
   
   assert_shape(shape);

   result.shape.row = shape.row; result.shape.col = shape.col;
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = value;

   return result;
}

/**
 * Return the shape of `matrix`.
 */
shape_t alat_matrix_shape(matrix_t matrix)
{
   assert_matrix(matrix);

   return matrix.shape;
}

/**
 * Create a new zeros matrix which has `shape`.
 */
matrix_t alat_matrix_zeros(shape_t shape) 
{
   return alat_matrix_arbitrary(0.0, shape);
}
 
/**
 * Create a new ones matrix which has `shape`.
 */
matrix_t alat_matrix_ones(shape_t shape)
{
   return alat_matrix_arbitrary(1.0, shape);
}

/**
 * Create a new identity matrix which has `shape`.
 */
matrix_t alat_matrix_identity(shape_t shape)
{
   int i, j;
   matrix_t result;

   assert_shape(shape);
   assert (shape.row == shape.col);

   result.shape.row = shape.row; 
   result.shape.col = shape.col;
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         if (i == j)
            result.matrix[i][j] = 1.0;
         else
            result.matrix[i][j] = 0.0;

   return result;
}

/**
 * Create sequential matrix which has `shape` and ranges between
 * `start` and `end`.
 */
matrix_t alat_matrix_sequential(double start, double end, shape_t shape)
{
   int i, j;
   double init, step;
   matrix_t result;

   assert_shape(shape);

   init = start;
   step = (double) (end - start) / (shape.row * shape.col - 1);
   result.shape.row = shape.row, result.shape.col = shape.col;
   for (i = 0; i<result.shape.row; i++)
      for (j = 0; j<result.shape.col; j++)
         result.matrix[i][j] = init, 
         init += step;

   return result;
}

/**
 * Create random matrix which has `shape`
 * and ranges between zero and one.
 */
matrix_t alat_matrix_random(shape_t shape)
{
   int i, j;
   double fvalue, svalue;
   matrix_t result;

   assert_shape(shape);

   i = 0; j = 0;
   srand((unsigned int) time(NULL));
   result.shape.row = shape.row;
   result.shape.col = shape.col;
   for (i = 0; i < result.shape.row; i++) {
      for (j = 0; j < result.shape.col; j++) {
         fvalue = rand(); 
         svalue = rand();
         if (fvalue >= svalue)
            result.matrix[i][j] = (svalue / fvalue);
         else
            result.matrix[i][j] = (fvalue / svalue);
      }
   }
   return result;
}

/**
 * Create uniform matrix which has `shape` and ranges its elements 
 * between `start` and `end`. It's recommended such usage `start` 
 * is negative and `end` is positive or the difference between 
 * `start` and `end` is much bigger.
 */
matrix_t alat_matrix_uniform(int start, int end, shape_t shape)
{
   int i, j, value;
   double element;
   matrix_t result, mrandom;

   assert_shape(shape);
   assert (end >= start);

   i = 0; j = 0;
   result.shape.row = shape.row; result.shape.col = shape.col;
   mrandom = alat_matrix_scalar_mul(alat_matrix_random(shape), 2);
   srand((unsigned int) time(NULL));

   while (true) {
      value = rand() % (end - start + 1);
      if (value % 2 == 0)
         element = value * mrandom.matrix[i][j];
      else 
         element = value * mrandom.matrix[i][j] * -1.0;
      if (element >= start && element <= end) 
         result.matrix[i][j] = element, j++;
      if (j == result.shape.col)
         i ++, j = 0;
      if (i == result.shape.row)
         break;
   }
   return result;
}

/**
 * Create randint matrix which has `shape` and ranges its
 * elements between `start` and `end`.
 */
matrix_t alat_matrix_randint(int start, int end, shape_t shape)
{
   int i, j;
   matrix_t result, muniform;

   assert_shape(shape);

   result.shape = shape;
   muniform = alat_matrix_uniform(start, end, shape);
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = (int) muniform.matrix[i][j];  

   return result;
}

/**
 * Return the diagonal matrix of `matrix`.
 */
matrix_t alat_matrix_diagonal(matrix_t matrix)
{
   int i;
   matrix_t result;

   assert_matrix(matrix);
   assert (alat_matrix_issquare(matrix));

   result.shape.row = 1, result.shape.col = matrix.shape.col;
   for (i = 0; i < matrix.shape.col; i++)
      result.matrix[0][i] = matrix.matrix[i][i];

   return result;
}

/** 
 * Return the max element in `matrix`. 
 */
double alat_matrix_max(matrix_t matrix)
{
   int i, j;
   double high;

   assert_matrix(matrix); 

   high = matrix.matrix[0][0];
   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         if (matrix.matrix[i][j] > high)
            high = matrix.matrix[i][j];

   return high;
}

/** 
 * Return the min element in `matrix`. 
 */
double alat_matrix_min(matrix_t matrix)
{
   int i, j;
   double low;

   assert_matrix(matrix);
   
   low = matrix.matrix[0][0];
   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         if (matrix.matrix[i][j] < low)
            low = matrix.matrix[i][j];

   return low;
}

/**
 * Return the value of `matrix` at which it resides in `place`.
 */
double alat_matrix_value(matrix_t matrix, place_t place)
{
   assert_matrix(matrix);
   assert_place(matrix, place);

   return matrix.matrix[place.crow][place.ccol];
}

/** 
 * Return the location of max element in `matrix`. `reverse`
 * must be `false` (as descending) or `true` (as ascending).
 */
place_t alat_matrix_argmax(matrix_t matrix, bool_t reverse)
{ 
   int i, j;
   double highest;
   place_t place;
   
   assert_matrix(matrix);
   assert (reverse == true || reverse == false);

   highest = alat_matrix_max(matrix);
   if (reverse == false) {
      for (i = matrix.shape.row - 1; i >= 0; i--)
         for (j = matrix.shape.col; j >= 0; j--)
            if (highest == (double) matrix.matrix[i][j])
               place.crow = i, place.ccol = j;
   }
   else {
      for (i = 0; i < matrix.shape.row; i++)
         for (j = 0; j < matrix.shape.col; j++)
            if (highest == (double) matrix.matrix[i][j])
               place.crow = i, place.ccol = j;
   }
   return place;
}
 
/** 
 * Return the location of max element in `matrix`. `reverse`
 * must be `false` (as descending) or `true` (as ascending).
 */
place_t alat_matrix_argmin(matrix_t matrix, bool_t reverse)
{
   int i, j;
   double lowest;
   place_t place;

   assert_matrix(matrix);
   assert (reverse == true || reverse == false);

   lowest = alat_matrix_min(matrix);
   if (reverse == false) {
      for (i = matrix.shape.row - 1; i >= 0; i--)
         for (j = matrix.shape.col; j >= 0; j--)
            if (lowest == (double) matrix.matrix[i][j])
               place.crow = i, place.ccol = j;
   }
   else {
      for (i = 0; i < matrix.shape.row; i++)
         for (j = 0; j < matrix.shape.col; j++)
            if (lowest == (double) matrix.matrix[i][j])
               place.crow = i,place.ccol = j;
   }
   return place;
}

/** 
 * Return the mean of `matrix`. 
 */
double alat_matrix_mean(matrix_t matrix)
{
   return alat_matrix_sum(alat_matrix_sum(matrix, 0), 1).matrix[0][0] / 
      (matrix.shape.row * matrix.shape.col);
}

/** 
 * Calculate the standard deviation of `matrix`. 
 */
double alat_matrix_stddev(matrix_t matrix)
{
   int i, j;
   double diff, total;

   assert_matrix(matrix);

   diff = 0, total = 0;
   for (i = 0; i < matrix.shape.row; i++) {
      for (j = 0; j < matrix.shape.col; j++) {
         diff = alat_matrix_mean(matrix) - matrix.matrix[i][j];
         if (diff < 0)
            total += pow(-1 * diff, 2);
         else
            total += pow(diff, 2);  
      }
   }
   return sqrt(total / (matrix.shape.row * matrix.shape.col));
}

/** 
 * Return the median element of `matrix`. 
 */
double alat_matrix_median(matrix_t matrix)
{
   int i, j, index, length;
   double array[matrix.shape.row * matrix.shape.col];
   matrix_t result;

   assert_matrix(matrix);

   index = 0;
   result = alat_matrix_sort(matrix, false);
   length = matrix.shape.row * matrix.shape.col;

   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         array[index] = matrix.matrix[i][j], index ++;

   if (length % 2 == 1)
      return array[(int) length / 2];
   else
      return (array[(int) length/2-1] + array[(int) length/2]) / 2;
}

/**
 * Calculate the 1-norm (maximum column sum) of `matrix`.
 */
double alat_matrix_norm_one(matrix_t matrix)
{
   int i, j;
   double sum, result;

   assert_matrix(matrix);

   result = 0.0;
   for (j = 0; j < matrix.shape.col; j++) {
      sum = 0.0;
      for (i = 0; i < matrix.shape.row; i++) 
         sum += fabs(matrix.matrix[i][j]);
      if (sum > result)
         result = sum;
   }      
   return result;
}

/**
 * Calculate the infinity (maximum row sum) norm of `matrix`.
 */
double alat_matrix_norm_infinity(matrix_t matrix)
{
   return alat_matrix_norm_one(alat_matrix_transpose(matrix));
}

/**
 * Calculate the frobenius norm of `matrix`.
 */
double alat_matrix_norm_frobenius(matrix_t matrix)
{
   int i, j;
   double result;

   assert_matrix(matrix);

   result = 0.0;
   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         result += pow(matrix.matrix[i][j], 2.0);

   return sqrt(result);
}

/**
 * Return the rank of `matrix`.
 */
int alat_matrix_rank(matrix_t matrix)
{
   int i, j, rank;
   row_t iszero;

   assert_matrix(matrix);

   iszero = 0;
   rank = 0;
   matrix = alat_matrix_uppertri(matrix);
   matrix = alat_matrix_abs(matrix);

   for (i = 0; i < matrix.shape.row; i++) {
      for (j = 0; j < matrix.shape.col; j++) 
         if (matrix.matrix[i][j] == 0.0)
            iszero += 1;
      if (iszero != matrix.shape.col)
         rank ++;
      iszero = 0;
   }
   return rank;
}

/**
 * Return the absolute of `matrix`.
 */
matrix_t alat_matrix_abs(matrix_t matrix)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);

   result.shape = matrix.shape; 
   for (i = 0; i < result.shape.row; i++) {
      for (j = 0; j < result.shape.col; j++) {
         if (matrix.matrix[i][j] < 0)
            result.matrix[i][j] = -1 * matrix.matrix[i][j];
         else
            result.matrix[i][j] = matrix.matrix[i][j];
      }
   }
   return result;
}

/**
 * Return the `n`.th power of `matrix`.
 */
matrix_t alat_matrix_pow(matrix_t matrix, double n)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);

   result.shape = matrix.shape;
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = pow(matrix.matrix[i][j], n);

   return result;
}

/**
 * Return the square of `matrix`.
 */
matrix_t alat_matrix_sqrt(matrix_t matrix)
{
   return alat_matrix_pow(matrix, 2.0);
}

/**
 * Return th `n`.th root of `matrix`.
 */
matrix_t alat_matrix_root(matrix_t matrix, double n)
{
   return alat_matrix_pow(matrix, 1 / n);
}

/** 
 * Convert the radians elements to degrees of `matrix`.
 */
matrix_t alat_matrix_degrees(matrix_t matrix)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);

   result.shape = matrix.shape;
   for (i = 0; i < result.shape.row; i++) 
      for (j = 0; j < result.shape.col; j++) 
         result.matrix[i][j] = DEG(matrix.matrix[i][j]);

   return result;
}

/**
 * Convert the degrees elements to radians of `matrix`.
 */
matrix_t alat_matrix_radians(matrix_t matrix)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);

   result.shape = matrix.shape;
   for (i = 0; i < result.shape.row; i++) 
      for (j = 0; j < result.shape.col; j++) 
         result.matrix[i][j] = RAD(matrix.matrix[i][j]);

   return result;
}

/**
 * Extract the subset from `matrix`. `fplace` and `splace` are respectively
 * start and end places at which subset matrix will be extracted.
 */
matrix_t alat_matrix_subset(matrix_t matrix, place_t fplace, place_t splace)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);
   assert_place(matrix, fplace);
   assert_place(matrix, splace);
   assert (fplace.crow < splace.crow && fplace.ccol < splace.ccol);

   result.shape.row = splace.crow - fplace.crow + 1;
   result.shape.col = splace.ccol - fplace.ccol + 1;

   for (i = fplace.crow; i <= splace.crow; i++)
      for (j = fplace.ccol; j <= splace.ccol; j++)
         result.matrix[i-fplace.crow][j-fplace.ccol] = matrix.matrix[i][j];

   return result;
}

/**
 * Insert the `value` into `crow`.th row of `matrix`.
 */
matrix_t alat_matrix_insert_row(matrix_t matrix, double value, row_t crow)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);
   assert (crow >= 0 && crow <= matrix.shape.row);

   result.shape.row = matrix.shape.row + 1;
   result.shape.col = matrix.shape.col;
   
   for (i = 0; i < crow; i++)
      for (j = 0; j < result.shape.col; j++) 
         result.matrix[i][j] = matrix.matrix[i][j];
   for (j = 0; j < result.shape.col; j++)
      result.matrix[crow][j] = value;
   for (i = crow; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++) 
         result.matrix[i + 1][j] = matrix.matrix[i][j];

   return result;
}

/**
 * Insert the `value` into `ccol`.th column of `matrix`.
 */
matrix_t alat_matrix_insert_col(matrix_t matrix, double value, col_t ccol)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);
   assert (ccol >= 0 && ccol <= matrix.shape.col);

   result.shape.row = matrix.shape.row;
   result.shape.col = matrix.shape.col + 1;

   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < ccol; j++)
         result.matrix[i][j] = matrix.matrix[i][j];
   for (i = 0; i < result.shape.row; i++)
      result.matrix[i][ccol] = value;
   for (i = 0; i < result.shape.row; i++)
      for (j = ccol; j < result.shape.col; j++)
         result.matrix[i][j + 1] = matrix.matrix[i][j];

   return result;
}

/**
 * Append the `value` at the last row of `matrix`.
 */
matrix_t alat_matrix_append_row(matrix_t matrix, double value)
{
   return alat_matrix_insert_row(matrix, value, matrix.shape.row);
}

/**
 * Append the `value` at the last column of `matrix`.
 */
matrix_t alat_matrix_append_col(matrix_t matrix, double value)
{
   return alat_matrix_insert_col(matrix, value, matrix.shape.col);
}

/**
 * Remove the `crow`.th row from the `matrix`.
 */
matrix_t alat_matrix_remove_row(matrix_t matrix, row_t crow)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);
   assert (crow >= 0 && crow < matrix.shape.row);

   result.shape.row = matrix.shape.row - 1;
   result.shape.col = matrix.shape.col;

   for (i = 0; i < crow; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = matrix.matrix[i][j];
   for (i = crow + 1; i < result.shape.row + 1; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i - 1][j] = matrix.matrix[i][j];

   return result;
}

/**
 * Remove the `ccol`.th column from `matrix`.
 */
matrix_t alat_matrix_remove_col(matrix_t matrix, col_t ccol)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);
   assert (ccol >= 0 && ccol < matrix.shape.col);

   result.shape.row = matrix.shape.row;
   result.shape.col = matrix.shape.col - 1;

   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < ccol; j++)
         result.matrix[i][j] = matrix.matrix[i][j];
   for (i = 0; i < result.shape.row; i++)
      for (j = ccol + 1; j < result.shape.col + 1; j++)
         result.matrix[i][j - 1] = matrix.matrix[i][j];

   return result;
}

/**
 * Remove the last row from `matrix`.
 */
matrix_t alat_matrix_pop_row(matrix_t matrix)
{
   return alat_matrix_remove_row(matrix, matrix.shape.row - 1);
}

/**
 * Remove the last column from `matrix`.
 */
matrix_t alat_matrix_pop_col(matrix_t matrix)
{
   return alat_matrix_remove_col(matrix, matrix.shape.col - 1);
}

/**
 * Sort the elements of `matrix`. `reverse` must be `true` 
 * (as ascending) or `false` (as descending).
 */
matrix_t alat_matrix_sort(matrix_t matrix, bool_t reverse)
{
   int i, j, index;
   double temp;
   double array[matrix.shape.row * matrix.shape.col];
   matrix_t result;

   assert_matrix(matrix);
   assert (reverse == true || reverse == false);

   result.shape = matrix.shape;
   index = 0;

   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         array[index] = matrix.matrix[i][j], index ++;
   for (i = 0; i < index; i++) {
      for (j = 0; j < index; j++) {
         if (reverse == false)
            if (array[i] < array[j])
               temp = array[i], array[i] = array[j], 
               array[j] = temp;
         if (reverse == true)
            if (array[i] > array[j])
               temp = array[i], array[i] = array[j], 
               array[j] = temp;
      }
   }
   for (i = result.shape.row - 1; i >= 0; i--)
      for (j = result.shape.col - 1; j >= 0; j--)
         result.matrix[i][j] = array[index - 1], index --;

   return result;  
}

/** 
 * Sum the elements of `matrix` according to `axis`.
 * `axis` must be `horizontal` or `vertical`.
 */
matrix_t alat_matrix_sum(matrix_t matrix, axis_t axis) 
{ 
   int i, j;
   double total;
   matrix_t result;

   assert_matrix(matrix);
   assert (axis == horizontal || axis == vertical);
 
   total = 0;

   if (axis == horizontal) {
      result.shape.row = 1; 
      result.shape.col = matrix.shape.col;
      for (j = 0; j < matrix.shape.col; j++) {
         for (i = 0; i < matrix.shape.row; i++) {
            total += matrix.matrix[i][j];
         }
         result.matrix[0][j] = total, total = 0;
      }
   } 
   else {
      result.shape.row = matrix.shape.row; 
      result.shape.col = 1;
      for (i = 0; i < matrix.shape.row; i++) {
         for (j = 0; j < matrix.shape.col; j++) {
            total += matrix.matrix[i][j];
         }
         result.matrix[i][0] = total, total = 0;
      }
   }
   return result;
}

/**
 * Suffle the elements of `matrix` randomly.
 */
matrix_t alat_matrix_shuffle(matrix_t matrix)
{
   int i, j, isthere, rvalue, index, el;
   int rindexes[matrix.shape.row * matrix.shape.col];
   double array[matrix.shape.row * matrix.shape.col];
   matrix_t result;

   assert_matrix(matrix);

   index = 0; 
   el = 0;
   srand((unsigned int) time(NULL));
   result.shape = matrix.shape;

   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         array[el] = matrix.matrix[i][j], el ++;

   while (true) {
      rvalue = rand() % (matrix.shape.row * matrix.shape.col);
      isthere = 0;
      for (i = 0; i < index; i++)
         if (rindexes[i] != rvalue)
            isthere ++;
      if (isthere == index)
         rindexes[index] = rvalue, index ++;
      if (index == matrix.shape.row * matrix.shape.col)
         break;
   }

   for (i = result.shape.row - 1; i >= 0; i--)
      for (j = result.shape.col - 1; j >= 0; j--)
         result.matrix[i][j] = array[rindexes[el-1]], el --;

   return result;
}

/**
 * Reshape the `matrix` according to `shape`. 
 */
matrix_t alat_matrix_reshape(matrix_t matrix, shape_t shape)
{
   int i, j, index;
   double array[matrix.shape.row * matrix.shape.col];
   matrix_t result;

   assert_matrix(matrix);
   assert_shape(shape);
   assert (matrix.shape.row * matrix.shape.col == shape.row * shape.col);

   result.shape = shape;
   index = 0;
   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         array[index] = matrix.matrix[i][j], index ++;
   index = 0;
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = array[index], index ++;

   return result;
}

/** 
 * Return the transpose of `matrix`. 
 */
matrix_t alat_matrix_transpose(matrix_t matrix)
{
   matrix_t result;

   assert_matrix(matrix);

   result.shape.row = matrix.shape.col;
   result.shape.col = matrix.shape.row;

   for (int i=0; i<matrix.shape.row; i++)
      for (int j=0; j<matrix.shape.col; j++)
         result.matrix[j][i] = matrix.matrix[i][j];

   return result;
}

/**
 * Concatenate the `fmatrix` and `smatrix` accroding to `axis`. `axis` 
 * must be `horizontal` or `vertical`.
 */
matrix_t alat_matrix_concat(matrix_t fmatrix, matrix_t smatrix, axis_t axis)
{
   int i, j;
   matrix_t result;

   assert_matrix(fmatrix);
   assert_matrix(smatrix);
   assert (axis == horizontal || axis == vertical); 
   assert ((axis == horizontal && fmatrix.shape.col == smatrix.shape.col) || 
      (axis = vertical && fmatrix.shape.row == smatrix.shape.row));

   if (axis == horizontal) {
      memcpy(&result, &fmatrix, sizeof(fmatrix));
      result.shape.row = fmatrix.shape.row + smatrix.shape.row;
      result.shape.col = fmatrix.shape.col;
      for (i = 0; i < smatrix.shape.row; i ++)
         for (j = 0; j < smatrix.shape.col; j++)
            result.matrix[i+fmatrix.shape.row][j] = smatrix.matrix[i][j];
   }
   else {
      memcpy(&result, &fmatrix, sizeof(fmatrix));
      result.shape.row = fmatrix.shape.row;
      result.shape.col = fmatrix.shape.col + smatrix.shape.col;
      for (i = 0; i < smatrix.shape.row; i ++)
         for (j = 0; j < smatrix.shape.col; j++)
            result.matrix[i][j+fmatrix.shape.col] = smatrix.matrix[i][j];
   }
   return result;
}

/**
 * Add the `fmatrix` and `smatrix` with each other.
 */
matrix_t alat_matrix_add(matrix_t fmatrix, matrix_t smatrix)
{
   int i, j;
   matrix_t result;

   assert_matrix(fmatrix);
   assert_matrix(smatrix);
   assert (fmatrix.shape.row == smatrix.shape.row && 
           smatrix.shape.col == smatrix.shape.col);

   result.shape = fmatrix.shape;
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = fmatrix.matrix[i][j] + smatrix.matrix[i][j];

   return result;
}

/**
 * Subtract the `smatrix` from `fmatrix`.
 */
matrix_t alat_matrix_sub(matrix_t fmatrix, matrix_t smatrix)
{
   int i, j;
   matrix_t result;

   assert_matrix(fmatrix);
   assert_matrix(smatrix);
   assert (fmatrix.shape.row == smatrix.shape.row && 
           smatrix.shape.col == smatrix.shape.col);

   result.shape = fmatrix.shape;
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = fmatrix.matrix[i][j] - smatrix.matrix[i][j];

   return result;
}

/**
 * Multiply the `matrix` with `scalar`.
 */
matrix_t alat_matrix_scalar_mul(matrix_t matrix, double scalar)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);

   result.shape = matrix.shape;
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = matrix.matrix[i][j] * scalar;

   return result;
}

/**
 * Multiply the `fmatrix` and `smatrix` with each other as dot.
 */
matrix_t alat_matrix_dot_mul(matrix_t fmatrix, matrix_t smatrix)
{
   int i, j;
   matrix_t result;

   assert_matrix(fmatrix);
   assert_matrix(smatrix);
   assert (fmatrix.shape.row == smatrix.shape.row && 
           smatrix.shape.col == smatrix.shape.col);

   result.shape = fmatrix.shape;
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = fmatrix.matrix[i][j] * smatrix.matrix[i][j];

   return result;
}

/**
 * Multiply the `fmatrix` and `smatrix` with each other as cross.
 */
matrix_t alat_matrix_cross_mul(matrix_t fmatrix, matrix_t smatrix)
{
   int i, j, k, start, index;
   double total, value, array[fmatrix.shape.row * smatrix.shape.col];
   matrix_t result, tmatrix;

   assert_matrix(fmatrix);
   assert_matrix(smatrix);
   assert (fmatrix.shape.col == smatrix.shape.row);   

   tmatrix = alat_matrix_transpose(smatrix);
   total = 0, start = 0, index = fmatrix.shape.col;
   result.shape.row = fmatrix.shape.row; 
   result.shape.col = smatrix.shape.col;

   for (i = 0; i < fmatrix.shape.row; i++)
      for (j = 0; j < smatrix.shape.col; j++)
         for (k = 0; k < smatrix.shape.row; k++) {
            value = fmatrix.matrix[i][k] * tmatrix.matrix[j][k];
            total += value;
            index --;
            if (index == 0) 
               array[start] = total, total = 0,
               index = fmatrix.shape.col, start ++;
         }
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = array[(int) total], total ++;

   return result;
}

/**
 * Divide the `matrix` by `scalar`.
 */
matrix_t alat_matrix_scalar_div(matrix_t matrix, double scalar)
{
   assert (scalar != 0.0);

   return alat_matrix_scalar_mul(matrix, 1 / scalar); 
}

/**
 * Swap the `matrix`.
 */
matrix_t alat_matrix_swap(matrix_t matrix)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);

   result.shape = matrix.shape; 
   for (i = 0; i < matrix.shape.row; i++) 
      for (j = 0; j < matrix.shape.col; j++) 
            result.matrix[i][j] = 1 / matrix.matrix[i][j];

   return result;
}

/**
 * Divide the `smatrix` using `fmatrix`.
 */
matrix_t alat_matrix_dot_div(matrix_t fmatrix, matrix_t smatrix)
{
   return alat_matrix_dot_mul(fmatrix, alat_matrix_swap(smatrix));
}

/**
 * Extract the upper triangle matrix from `matrix`.
 */
matrix_t alat_matrix_uppertri(matrix_t matrix)
{
   int i, j, k;
   row_t nonzero;
   double coef, array[matrix.shape.row];
   shape_t shape;
   matrix_t fsubmat, ssubmat, muled;

   assert_matrix(matrix);

   k = 0;
   nonzero = -1;
   shape.row = 1, shape.col = matrix.shape.col;
   fsubmat = alat_matrix_zeros(shape);
   ssubmat = alat_matrix_zeros(shape);

   while (true) {
      for (i = 1 + k; i < matrix.shape.row; i++) {
         if (matrix.matrix[k][k] == 0.0) {
            for (j = 0; j < matrix.shape.row; j++)
               if (matrix.matrix[j][k] != 0.0)
                  nonzero = j;
            for (j = 0; j < matrix.shape.col; j++) {
               array[j] = matrix.matrix[k][j];
               matrix.matrix[k][j] = matrix.matrix[nonzero][j];
               matrix.matrix[nonzero][j] = array[j];
            }
         }
         coef = -1.0 * matrix.matrix[i][k] / matrix.matrix[k][k];
         for (j = 0; j < matrix.shape.col; j++) {
            fsubmat.matrix[0][j] = matrix.matrix[k][j];
            ssubmat.matrix[0][j] = matrix.matrix[i][j];
         }
         muled = alat_matrix_add(ssubmat, alat_matrix_scalar_mul(fsubmat, coef));
         for (j = 0; j < matrix.shape.col; j++)
            matrix.matrix[i][j] = muled.matrix[0][j];
      }
      k ++;
      if (k == matrix.shape.row)
         break;
   }
   return matrix;
}

/** 
 * Calculate the determinant of `matrix`. 
 */
double alat_matrix_det(matrix_t matrix)
{
   int i;
   double result;

   assert_matrix(matrix);
   assert (alat_matrix_issquare(matrix));

   result = 1.0;
   matrix = alat_matrix_uppertri(matrix);

   for (i = 0; i < matrix.shape.row; i++)
      result *= matrix.matrix[i][i];

   return result;
}

/**
 * Extract the minors map from `matrix`.
 */
matrix_t alat_matrix_minors(matrix_t matrix)
{
   int i, j, k, l, index;
   matrix_t result, fparsed, tparsed, sparsed;

   assert_matrix(matrix);
   assert (alat_matrix_issquare(matrix));

   index = 0;
   result.shape = matrix.shape;
   fparsed.shape.row = matrix.shape.row - 1;
   fparsed.shape.col = matrix.shape.col;
   sparsed.shape.row = matrix.shape.row - 1;
   sparsed.shape.col = matrix.shape.col - 1;

   for (i = 0; i < matrix.shape.row; i++) {
      for (k = 0; k < i; k++) {
         for (l = 0; l < matrix.shape.col; l++)
            fparsed.matrix[index][l] = matrix.matrix[k][l];
         index ++;
      }
      for (k = i + 1; k < matrix.shape.row; k++) {
         for (l = 0; l < matrix.shape.col; l++)
            fparsed.matrix[index][l] = matrix.matrix[k][l];
         index ++;
      }
      index = 0;
      tparsed = alat_matrix_transpose(fparsed);
      for (j = 0; j < tparsed.shape.row; j++) {
         for (k = 0; k < j; k++) {
            for (l = 0; l < tparsed.shape.col; l++)
               sparsed.matrix[index][l] = tparsed.matrix[k][l];
            index ++;
         }
         for (k = j + 1; k < tparsed.shape.row; k++) {
            for (l = 0; l < tparsed.shape.col; l++)
               sparsed.matrix[index][l] = tparsed.matrix[k][l];
            index ++;
         }
         index = 0;
         result.matrix[i][j] = alat_matrix_det(alat_matrix_transpose(sparsed));
      }
   }
   return result;
}

/**
 * Extract the cofactors map from 'matrix'.
 */
matrix_t alat_matrix_cofactors(matrix_t matrix)
{
   int i, j;
   matrix_t result;

   assert_matrix(matrix);
   assert (alat_matrix_issquare(matrix));

   result = alat_matrix_minors(matrix);
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         if ((i + j) % 2 == 1 && result.matrix[i][j] != 0.0)
            result.matrix[i][j] = -1 * result.matrix[i][j];

   return result;
}

/**
 *  Calculate the adjoint of `matrix`. 
 */
matrix_t alat_matrix_adjoint(matrix_t matrix)
{
   return alat_matrix_transpose(alat_matrix_cofactors(matrix));
}

/**
 * Calculate the inverse of `matrix`.
 */
matrix_t alat_matrix_inverse(matrix_t matrix)
{
   assert (alat_matrix_isinvertible(matrix));

   return alat_matrix_scalar_div(alat_matrix_adjoint(matrix), 
          alat_matrix_det(matrix));
}

/**
 * Extract the lower triangle matrix from `matrix.`
 */
matrix_t alat_matrix_lowertri(matrix_t matrix)
{
   return alat_matrix_cross_mul(matrix, 
      alat_matrix_inverse(alat_matrix_uppertri(matrix)));
}
 
/**
 * Solve the linear equation. `matrix` must 
 * include the both main and target matrices.
 */
matrix_t alat_matrix_solve(matrix_t matrix)
{
   int i, j;
   matrix_t main, target;

   assert_matrix(matrix);
   assert (matrix.shape.col - matrix.shape.row == 1);

   main.shape.row = matrix.shape.row; 
   main.shape.col = matrix.shape.col - 1;
   target.shape.row = matrix.shape.row, target.shape.col = 1;

   for (i = 0; i < main.shape.row; i++)
      for (j = 0; j < main.shape.col; j++)
         main.matrix[i][j] = matrix.matrix[i][j];
   for (i = 0; i < target.shape.row; i++)
      for (j = 0; j < target.shape.col; j++)
         target.matrix[i][j] = matrix.matrix[i][matrix.shape.col-1];

   return alat_matrix_cross_mul(alat_matrix_inverse(main), target);
}
