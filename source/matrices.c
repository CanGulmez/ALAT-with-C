/* Matrix operations for ALAT (Advanced Linear Algebra Toolkit) */

#include "./alat.h"

/**
 * Return true, if `matrix` is square, otherwise return false. 
 */
bool_t matrices_issquare(matrix_t matrix) 
{
   return (matrix.shape.row == matrix.shape.col) ? true : false;
}  

/** 
 * Return true, if `matrix` is homogen, otherwise return false. 
 */
bool_t matrices_ishomogen(matrix_t matrix) 
{
   for (int i=0; i<matrix.shape.row; i++)
      if (matrix.matrix[i][matrix.shape.col-1] != 0)
         return false;

   return true;
}

/** 
 * Return true, if `matrix` just contains `value`s, otherwise return false. 
 */
bool_t matrices_isarbitrary(matrix_t matrix, double value) 
{
   for (int i=0; i<matrix.shape.row; i++)
      for (int j=0; j<matrix.shape.col; j++)
         if (matrix.matrix[i][j] != value)
            return false;

   return true;
}

/** 
 * Return true, if `matrix` just contains 0s, otherwise return false. 
 */
bool_t matrices_iszeros(matrix_t matrix) 
{
   return (matrices_isarbitrary(matrix, 0.0)) ? true : false;
}

/** 
 * Return true, if `matrix` just contains 1s, otherwise return false. 
 */
bool_t matrices_isones(matrix_t matrix) 
{
   return (matrices_isarbitrary(matrix, 1.0)) ? true : false;
}

/** 
 * Return true, if `matrix` is identity, otherwise return false. 
 */
bool_t matrices_isidentity(matrix_t matrix)
{
   for (int i=0; i<matrix.shape.row; i++)
      for (int j=0; j<matrix.shape.col; j++)
         if ((i == j && matrix.matrix[i][j] != 1.0) || 
             (i != j && matrix.matrix[i][j] != 0.0))
               return false;

   return true;
}

/** 
 * Return true, if `matrix` is upper triangle, otherwise return false. 
 */
bool_t matrices_isuppertri(matrix_t matrix) 
{
   if (matrices_issquare(matrix) == false)
      return false; 

   for (int i=1; i<matrix.shape.row; i++)
      for (int j=0; j<i; j++)
         if (matrix.matrix[i][j] != 0.0)
            return false;

   return true;
}

/** 
 * Return true, if `matrix` is lower triangle, otherwise return false. 
 */
bool_t matrices_islowertri(matrix_t matrix)
{
   return (matrices_isuppertri(matrices_transpose(matrix))) ? true : false;
}

/** 
 * Return true, if `matrix` is upper or lower triangular, otherwise 
 * return false.
 */
bool_t matrices_istriangle(matrix_t matrix)
{
   return (matrices_islowertri(matrix) || matrices_isuppertri(matrix)) ? true : false;
}

/**
 * Return true, if `matrix` is diagonal, otherwise return false.
 */
bool_t matrices_isdiagonal(matrix_t matrix)
{
   return (matrices_isuppertri(matrix) && matrices_islowertri(matrix)) ? true : false;
}

/**
 * Return true, if `matrix` is symmetric, otherwise return false.
 */
bool_t matrices_issymmetric(matrix_t matrix)
{
   return (matrices_isequal(matrix, matrices_transpose(matrix))) ? true : false;
}

/**
 * Return true, if `fmatrix` and `smatrix` are equals, otherwise, 
 * return false.
 */
bool_t matrices_isequal(matrix_t fmatrix, matrix_t smatrix)
{
   if (fmatrix.shape.row != smatrix.shape.row ||
       fmatrix.shape.col != smatrix.shape.col)
      return false;

   for (int i=0; i<fmatrix.shape.row; i++)
      for (int j=0; j<fmatrix.shape.col; j++)
         if (fmatrix.matrix[i][j] != smatrix.matrix[i][j])
            return false;

   return true;
}
 
/** 
 * Return true, if `matrix` is invertible, otherwise return false. 
 */
bool_t matrices_isinvertible(matrix_t matrix)
{
   return (matrices_det(matrix) != 0.0) ? true : false;
}

/** 
 * Create a new arbitrary matrix and return it. Matrix just will
 * contains `value`. Matrix's shape will be `shape`.
 */
matrix_t matrices_arbitrary(double value, shape_t shape) 
{
   matrix_t result;
   int i, j;

   result.shape.row = shape.row, result.shape.col = shape.col;
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = value;

   return result;
}

/**
 * Create a new zeros matrix and return it. Matrix just will 
 * contians zeros. Matrix's shape will be `shape`.
 */
matrix_t matrices_zeros(shape_t shape) 
{
   return matrices_arbitrary(0.0, shape);
}

/**
 * Create a new ones matrix and return it. Matrix just will
 * contains ones. Matrix's shape will be `shape`.
 */
matrix_t matrices_ones(shape_t shape)
{
   return matrices_arbitrary(1.0, shape);
}

/**
 * Create a new identity matrix and return it. Matrix's shape 
 * will be `shape` and must be square.
 */
matrix_t matrices_identity(shape_t shape)
{
   matrix_t result;
   int i, j;

   if (shape.row != shape.col) 
      alat_error("Square matrix error");

   result.shape.row = shape.row, result.shape.col = shape.col;
   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         if (i == j)
            result.matrix[i][j] = 1.0;
         else
            result.matrix[i][j] = 0.0;

   return result;
}

/**
 * Create a new sequential matrix. All elements in sequential
 * matrix will range `start` to `end`. Sequential matrix's shape
 * will be `shape`.
 */
matrix_t matrices_sequential(int start, int end, shape_t shape)
{
   matrix_t result;
   double init, step;
   int i, j;

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
 * Create a random matrix. All elements in the random matrix 
 * ranges 0 to 1. Matrix's shape will be `shape`.
 */
matrix_t matrices_random(shape_t shape)
{
   matrix_t result;
   int i, j;
   double fvalue, svalue;

   i = 0; j = 0;
   srand((unsigned int) time(NULL));
   result.shape.row = shape.row, result.shape.col = shape.col;

   // Create two random numbers and divide them with each other 
   // to obtain floating-point number between 0 and 1. 
   for (i = 0; i < result.shape.row; i++) {
      for (j = 0; j < result.shape.col; j++) {

         fvalue = rand(); svalue = rand();

         if (fvalue >= svalue)
            result.matrix[i][j] = (svalue / fvalue);
         else
            result.matrix[i][j] = (fvalue / svalue);
      }
   }

   return result;
}

/**
 * Create a uniform matrix. All elements in the uniform matrix
 * will range `start` to `end`. Uniform matrix's shape will be 
 * 'shape'.
 */
matrix_t matrices_uniform(int start, int end, shape_t shape)
{
   matrix_t result, mrandom;
   double element;
   int i, j, value;

   if (end < start)
      alat_error("'end' must be equal or bigger than 'start'");

   i = 0; j = 0;
   result.shape.row = shape.row; result.shape.col = shape.col;
   mrandom = matrices_scaler_mul(matrices_random(shape), 2);
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
 * Create a randint matrix. All elements in the randint matrix
 * will range `start` to `end`. Randint matrix's shape will be
 * `shape`.
 */
matrix_t matrices_randint(int start, int end, shape_t shape)
{
   matrix_t result, muniform;
   int i, j;

   muniform = matrices_uniform(start, end, shape);
   result.shape = shape;

   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = (int) muniform.matrix[i][j];  

   return result;
}
 
/**
 * Get the diagonal matrix of square `matrix`.
 */
matrix_t matrices_diagonal(matrix_t matrix)
{
   matrix_t result;
   int i;

   if (matrix.shape.row != matrix.shape.col) 
      alat_error("Square matrix error");

   result.shape.row = 1, result.shape.col = matrix.shape.col;
   for (i = 0; i < matrix.shape.col; i++)
      result.matrix[0][i] = matrix.matrix[i][i];

   return result;
}

/** 
 * Find the highest element in `matrix` and return it. 
 */
double matrices_max(matrix_t matrix)
{
   double high;
   int i, j;

   high = matrix.matrix[0][0];

   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         if (matrix.matrix[i][j] > high)
            high = matrix.matrix[i][j];

   return high;
}

/** 
 * Find the lowest element in `matrix` and return it. 
 */
double matrices_min(matrix_t matrix)
{
   double low;
   int i, j;

   low = matrix.matrix[0][0];

   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         if (matrix.matrix[i][j] < low)
            low = matrix.matrix[i][j];

   return low;
}

/** 
 * Find the index of the highest element in `matrix`. `reverse` 
 * indicates the flow direction. If `reverse` is true, in this 
 * case flow direction starts from end elements. If `reverse` is 
 * false, in this case flow direction starts from first element.
 */
shape_t matrices_elmax(matrix_t matrix, bool_t reverse)
{
   double highest;
   shape_t shape;
   int i, j;

   if (reverse != true && reverse != false)
      alat_error("'reverse' must be true or false");

   highest = matrices_max(matrix);

   if (reverse == false) {
      for (i = matrix.shape.row - 1; i >= 0; i--)
         for (j = matrix.shape.col; j >= 0; j--)
            if (highest == (double) matrix.matrix[i][j])
               shape.row = i, shape.col = j;
   }
   else {
      for (i = 0; i < matrix.shape.row; i++)
         for (j = 0; j < matrix.shape.col; j++)
            if (highest == (double) matrix.matrix[i][j])
               shape.row = i, shape.col = j;
   }

   return shape;
}
 
/** 
 * Find the index of the lowest element in `matrix`. `reverse` 
 * indicates the flow direction. If `reverse` is true, in this 
 * case flow direction starts from end elements. If `reverse` is 
 * false, in this case flow direction starts from first element.
 */
shape_t matrices_elmin(matrix_t matrix, bool_t reverse)
{
   double lowest;
   shape_t shape;
   int i, j;

   if (reverse != true && reverse != false)
      alat_error("'reverse' must be true or false");

   lowest = matrices_min(matrix);

   if (reverse == false) {
      for (i = matrix.shape.row - 1; i >= 0; i--)
         for (j = matrix.shape.col; j >= 0; j--)
            if (lowest == (double) matrix.matrix[i][j])
               shape.row = i, shape.col = j;
   }
   else {
      for (i = 0; i < matrix.shape.row; i++)
         for (j = 0; j < matrix.shape.col; j++)
            if (lowest == (double) matrix.matrix[i][j])
               shape.row = i, shape.col = j;
   }

   return shape;
}

/** 
 * Calculate the mean of `matrix` and return it. 
 */
double matrices_mean(matrix_t matrix)
{
   return matrices_sum(matrices_sum(matrix, 0), 1).matrix[0][0] / 
          (matrix.shape.row * matrix.shape.col);
}

/** 
 * Calculate the standard deviation of `matrix`. 
 */
double matrices_stddev(matrix_t matrix)
{
   double diff, total;
   int i, j;

   diff = 0, total = 0;

   for (i = 0; i < matrix.shape.row; i++) {
      for (j = 0; j < matrix.shape.col; j++) {
         diff = matrices_mean(matrix) - matrix.matrix[i][j];
         if (diff < 0)
            total += pow(-1 * diff, 2);
         else
            total += pow(diff, 2);  
      }
   }

   return sqrt(total / (matrix.shape.row * matrix.shape.col));
}

/** 
 * Find the median element of `matrix` and return it. 
 */
double matrices_median(matrix_t matrix)
{
   matrix_t sorted;
   double array[matrix.shape.row * matrix.shape.col];
   int i, j, index, length;

   index = 0;
   sorted = matrices_sort(matrix, false);
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
 * Get the absolute of `matrix`.
 */
matrix_t matrices_abs(matrix_t matrix)
{
   matrix_t result;
   int i, j;

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
 * Get the `n`.th power of `matrix`.
 */
matrix_t matrices_pow(matrix_t matrix, double n)
{
   matrix_t result;
   int i, j;

   result.shape = matrix.shape;

   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = pow(matrix.matrix[i][j], n);

   return result;
}

/**
 * Get th `n`.th root of `matrix`.
 */
matrix_t matrices_root(matrix_t matrix, double n)
{
   return matrices_pow(matrix, 1 / n);
}

/* Convert the `matrix` which contains randians to degrees. */
matrix_t matrices_degrees(matrix_t matrix)
{
   matrix_t result;
   int i, j;

   result.shape = matrix.shape;

   for (i = 0; i < result.shape.row; i++) 
      for (j = 0; j < result.shape.col; j++) 
         result.matrix[i][j] = DEG(matrix.matrix[i][j]);

   return result;
}

/* Convert the `matrix` which contains degrees to radians. */
matrix_t matrices_radians(matrix_t matrix)
{
   matrix_t result;
   int i, j;

   result.shape = matrix.shape;

   for (i = 0; i < result.shape.row; i++) 
      for (j = 0; j < result.shape.col; j++) 
         result.matrix[i][j] = RAD(matrix.matrix[i][j]);

   return result;
}

/**
 * Sort the elements of `matrix`. `reverse` must be true (as 
 * ascending) or false (as descending).
 */
matrix_t matrices_sort(matrix_t matrix, bool_t reverse)
{
   matrix_t result;
   double array[matrix.shape.row * matrix.shape.col];
   int i, j, index;
   double temp;

   result.shape = matrix.shape;
   index = 0;

   if (reverse != true && reverse != false) 
      alat_error("'reverse' must be 'true' or 'false'");

   // Convert the 'matrix' into 'array' to sort.
   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         array[index] = matrix.matrix[i][j], index ++;

   // Sort the 'array' according to 'reverse'.
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

   // Convert back sorted 'array' to 'result' and return it.
   for (i = result.shape.row - 1; i >= 0; i--)
      for (j = result.shape.col - 1; j >= 0; j--)
         result.matrix[i][j] = array[index - 1], index --;

   return result;  
}

/** 
 * Aggregate the `matrix` according to `axis`. `axis` must be 0 
 * (horizontally) or 1 (vertically), otherwise return error.
 */
matrix_t matrices_sum(matrix_t matrix, int axis)
{
   matrix_t result;
   double total;
   int i, j;

   total = 0;

   if (axis != 0 && axis != 1) 
      alat_error("'axis' must be 0 (horizontal) or 1 (vertical)");

   // Aggregate the 'matrix' as horizontally.
   if (axis == 0) {
      result.shape.row = 1, result.shape.col = matrix.shape.col;

      for (j = 0; j < matrix.shape.col; j++) {
         for (i = 0; i < matrix.shape.row; i++) {
            total += matrix.matrix[i][j];
         }
         result.matrix[0][j] = total, total = 0;
      }
   } 
   // Aggregate the 'matrix' as vertically.
   else {
      result.shape.row = matrix.shape.row, result.shape.col = 1;

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
matrix_t matrices_shuffle(matrix_t matrix)
{
   matrix_t result;
   int rindexes[matrix.shape.row * matrix.shape.col];
   double array[matrix.shape.row * matrix.shape.col];
   int i, j, isthere, rvalue, index, el;

   index = 0; 
   el = 0;
   srand((unsigned int) time(NULL));
   result.shape = matrix.shape;

   // Convert the 'matrix' into an 'array'.
   for (i = 0; i < matrix.shape.row; i++)
      for (j = 0; j < matrix.shape.col; j++)
         array[el] = matrix.matrix[i][j], el ++;

   // Create the random indexes to shuffle 'matrix'.
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

   // Fill the 'result' with random indexes and return it.
   for (i = result.shape.row - 1; i >= 0; i--)
      for (j = result.shape.col - 1; j >= 0; j--)
         result.matrix[i][j] = array[rindexes[el-1]], el --;

   return result;
}

/**
 * Reshape the `matrix` according to `shape`. `shape` will determine 
 * new shape of `matrix`.
 */
matrix_t matrices_reshape(matrix_t matrix, shape_t shape)
{
   matrix_t result;
   double array[matrix.shape.row * matrix.shape.col];
   int i, j, index;

   result.shape = shape;
   index = 0;

   if (matrix.shape.row * matrix.shape.col != shape.row * shape.col) 
      alat_error("Dimension dismatch found");

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
matrix_t matrices_transpose(matrix_t matrix)
{
   matrix_t result;

   result.shape.row = matrix.shape.col;
   result.shape.col = matrix.shape.row;

   for (int i=0; i<matrix.shape.row; i++)
      for (int j=0; j<matrix.shape.col; j++)
         result.matrix[j][i] = matrix.matrix[i][j];

   return result;
}

/**
 * Concatenate the `fmatrix` and `smatrix` accroding to `axis`.
 * `axis` must be 0 (as horizontally) or 1 (as vertically).
 */
matrix_t matrices_concat(matrix_t fmatrix, matrix_t smatrix, int axis)
{
   matrix_t result;
   int i, j;

   if (axis != 0 && axis != 1) 
      alat_error("'axis' must be 0 (horizontal) or 1 (vertical)");

   if ((axis == 0 && fmatrix.shape.col != smatrix.shape.col) ||
       (axis == 1 && fmatrix.shape.row != smatrix.shape.row)) 
      alat_error("Dimension dismatch found");

   // Concatenate the matrices as horizontally.
   if (axis == 0) {
      memcpy(&result, &fmatrix, sizeof(fmatrix));
      result.shape.row = fmatrix.shape.row + smatrix.shape.row;
      result.shape.col = fmatrix.shape.col;

      for (i = 0; i < smatrix.shape.row; i ++)
         for (j = 0; j < smatrix.shape.col; j++)
            result.matrix[i+fmatrix.shape.row][j] = smatrix.matrix[i][j];
   }
   // Concatenate the matrices as vertically.
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
matrix_t matrices_add(matrix_t fmatrix, matrix_t smatrix)
{
   matrix_t result;
   int i, j;

   if ((fmatrix.shape.row != smatrix.shape.row) || 
       (fmatrix.shape.col != smatrix.shape.col)) 
      alat_error("Dimension dismatch found");

   result.shape = fmatrix.shape;

   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = fmatrix.matrix[i][j] + smatrix.matrix[i][j];

   return result;
}

/**
 * Subtract the `smatrix` from `fmatrix`.
 */
matrix_t matrices_subtract(matrix_t fmatrix, matrix_t smatrix)
{
   matrix_t result;
   int i, j;

   if ((fmatrix.shape.row != smatrix.shape.row) || 
       (fmatrix.shape.col != smatrix.shape.col)) 
      alat_error("dimension dismatch found");

   result.shape = fmatrix.shape;

   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = fmatrix.matrix[i][j] - smatrix.matrix[i][j];

   return result;
}

/**
 * Multiply the `matrix` with `scaler`.
 */
matrix_t matrices_scaler_mul(matrix_t matrix, double scaler)
{
   matrix_t result;
   int i, j;

   result.shape = matrix.shape;

   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = matrix.matrix[i][j] * scaler;

   return result;
}

/**
 * Multiply the `fmatrix` and `smatrix` with each other as dot.
 */
matrix_t matrices_dot_mul(matrix_t fmatrix, matrix_t smatrix)
{
   matrix_t result;
   int i, j;

   if ((fmatrix.shape.row != smatrix.shape.row) || 
       (fmatrix.shape.col != smatrix.shape.col)) 
      alat_error("Dimension dismatch found");

   result.shape = fmatrix.shape;

   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = fmatrix.matrix[i][j] * smatrix.matrix[i][j];

   return result;
}

/**
 * Multiply the `fmatrix` and `smatrix` with each other as cross.
 */
matrix_t matrices_cross_mul(matrix_t fmatrix, matrix_t smatrix)
{
   matrix_t result;
   int i, j, k, start, index;
   double total, value, array[fmatrix.shape.row * smatrix.shape.col];

   if (fmatrix.shape.col != smatrix.shape.row) 
      alat_error("Dimension dismatch found");

   matrix_t tmatrix = matrices_transpose(smatrix);
   total = 0, start = 0, index = fmatrix.shape.col;
   result.shape.row = fmatrix.shape.row, result.shape.col = smatrix.shape.col;

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
 * Divide the `matrix` using `scaler`.
 */
matrix_t matrices_scaler_div(matrix_t matrix, double scaler)
{
   if (scaler == 0.0) 
      alat_error("Zero division error");

   return matrices_scaler_mul(matrix, 1 / scaler); 
}

/**
 * Swap the `matrix`.
 */
matrix_t matrices_swap(matrix_t matrix)
{
   matrix_t result;
   int i, j;

   result.shape = matrix.shape; 

   for (i = 0; i < matrix.shape.row; i++) {
      for (j = 0; j < matrix.shape.col; j++) {
         if (matrix.matrix[i][j] == 0.0) 
            alat_error("Zero division error");
         else
            result.matrix[i][j] = 1 / matrix.matrix[i][j];
      }
   }
   return result;
}

/**
 * Divide the `smatrix` using `fmatrix`.
 */
matrix_t matrices_dot_div(matrix_t fmatrix, matrix_t smatrix)
{
   return matrices_dot_mul(fmatrix, matrices_swap(smatrix));
}

/** 
 * Calculate the determinant of `matrix`. 
 */
double matrices_det(matrix_t matrix)
{
   matrix_t fsubmat, ssubmat, res;
   double det, coef, array[matrix.shape.row];
   int i, j, k, switching, nonzero;

   if (matrix.shape.row != matrix.shape.col) 
      alat_error("Dimension dimatch found");

   k = 0; switching = 1; nonzero = -1; det = 1.0;

   // Calculate the determinant of 1x1 matrix.
   if (matrix.shape.row == 1)
      return matrix.matrix[0][0];

   // Calculate the determinant of 2x2 matrix.
   if (matrix.shape.row == 2)
      return matrix.matrix[0][0] * matrix.matrix[1][1] - 
             matrix.matrix[0][1] * matrix.matrix[1][0];

   // Calculate the determinant of 3x3 and more matrix.
   while (true) {
      for (i = 1 + k; i < matrix.shape.row; i++) {

         fsubmat.shape.row = 1; fsubmat.shape.col = matrix.shape.col;
         ssubmat.shape.row = 1; ssubmat.shape.col = matrix.shape.col;

         // If the main diagonal of 'matrix' contains zero, in this 
         // case make replacement between rows of 'matrix'.
         if (matrix.matrix[k][k] == 0.0) {
            // Find the nonzero element in the diagonal.
            for (j = 0; j < matrix.shape.row; j++)
               if (matrix.matrix[j][k] != 0.0)
                  nonzero = j;
            // Iff all elements of an column are zeros, exit process.
            if (nonzero == -1)
               return 0;

            for (j = 0; j < matrix.shape.col; j++) {
               array[j] = matrix.matrix[k][j];
               matrix.matrix[k][j] = matrix.matrix[nonzero][j];
               matrix.matrix[nonzero][j] = array[j];
            }
            switching *= -1;
         }
         // Calculate the coefficient of related rows.
         coef = -1 * matrix.matrix[i][k] / matrix.matrix[k][k];

         // Prepare the rows to replace with each other.
         for (j = 0; j < matrix.shape.col; j++) {
            fsubmat.matrix[0][j] = matrix.matrix[k][j];
            ssubmat.matrix[0][j] = matrix.matrix[i][j];
         }
         res = matrices_add(ssubmat, matrices_scaler_mul(fsubmat, coef));

         for (j = 0; j < matrix.shape.col; j++)
            matrix.matrix[i][j] = res.matrix[0][j];
      }
      // Break up the loop after the upper triangle matrix occured.
      k ++;
      if (k == matrix.shape.row)
         break;
   }
   // Calculate the determinant of 'matrix' using triangle matrix.
   for (i = 0; i < matrix.shape.row; i++)
      det *= matrix.matrix[i][i];

   return det * switching;
}

/**
 * Extract the minors map from `matrix`.
 */
matrix_t matrices_minors(matrix_t matrix)
{
   matrix_t result, fparsed, tparsed, sparsed;
   int i, j, k, l, index;

   index = 0;
   result.shape = matrix.shape;
   fparsed.shape.row = matrix.shape.row - 1;
   fparsed.shape.col = matrix.shape.col;
   sparsed.shape.row = matrix.shape.row - 1;
   sparsed.shape.col = matrix.shape.col - 1;

   if (matrix.shape.row != matrix.shape.col)
      alat_error("Dimension dismatch found");

   for (i = 0; i < matrix.shape.row; i++) {

      // Delete the i.th row from 'matrix' and create the submatrices.
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

      // Get the transpose of submatrices to delete columns in order.
      tparsed = matrices_transpose(fparsed);

      for (j = 0; j < tparsed.shape.row; j++) {

         // Delete the j.th column and create submatrices.
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

         // Get the determinant and append it to result matrix.
         result.matrix[i][j] = matrices_det(matrices_transpose(sparsed));
      }
   }

   return result;
}

/**
 * Extract the cofactors map from 'matrix'.
 */
matrix_t matrices_cofactors(matrix_t matrix)
{
   matrix_t result;
   int i, j;

   result = matrices_minors(matrix);

   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         if ((i + j) % 2 == 1 && result.matrix[i][j] != 0.0)
            result.matrix[i][j] = -1 * result.matrix[i][j];

   return result;
}

/**
 *  Calculate the adjoint of `matrix`. 
 */
matrix_t matrices_adjoint(matrix_t matrix)
{
   return matrices_transpose(matrices_cofactors(matrix));
}

/**
 * Calculate the inverse of `matrix`.
 */
matrix_t matrices_inverse(matrix_t matrix)
{
   if (!matrices_isinvertible(matrix)) 
      alat_error("Non-invetible matrix found");

   return matrices_scaler_div(matrices_adjoint(matrix), 
                              matrices_det(matrix));
}

/**
 * Solve the linear equation. `matrix` must be augmented form
 * so that `matrix` includes both main and target equations.
 */
matrix_t matrices_solve(matrix_t matrix)
{
   matrix_t main, target;
   int i, j;

   if (matrix.shape.col - matrix.shape.row != 1)
      alat_error("'matrix' must be augmented form");

   main.shape.row = matrix.shape.row; 
   main.shape.col = matrix.shape.col - 1;
   target.shape.row = matrix.shape.row, target.shape.col = 1;

   // Extract the 'main' and 'target' matrices.
   for (i = 0; i < main.shape.row; i++)
      for (j = 0; j < main.shape.col; j++)
         main.matrix[i][j] = matrix.matrix[i][j];
   
   for (i = 0; i < target.shape.row; i++)
      for (j = 0; j < target.shape.col; j++)
         target.matrix[i][j] = matrix.matrix[i][matrix.shape.col-1];

   return matrices_cross_mul(matrices_inverse(main), target);
}
