/* Vector operations in ALAT (Advanced Linear Algebra Toolkit) */

#include "./utils.h"

/**
 * Return true if `vector` just contains zeros, 
 * otherwise return false.
 */
bool_t vectors_iszeros(vector_t vector)
{
   return vectors_isarbitrary(vector, 0.0);
}

/**
 * Return true if `vector` just contains ones, 
 * otherwise return false.
 */
bool_t vectors_isones(vector_t vector)
{
   return vectors_isarbitrary(vector, 1.0);
}

/**
 * Return true if `vector` just contains `value`s, otherwise
 * return false.
 */
bool_t vectors_isarbitrary(vector_t vector, double value)
{
   int i;

   for (i = 0; i < vector.dim; i++)
      if (vector.vector[i] != value)
         return false;

   return true;
}

/**
 * Return true, if `fvector` and `svector` are same, otherwise
 * return false.
 */
bool_t vectors_isequal(vector_t fvector, vector_t svector)
{
   int i;

   if (fvector.dim != svector.dim)
      return false;

   for (i = 0; i < fvector.dim; i++)
      if (fvector.vector[i] != svector.vector[i])
         return false;

   return true;
}

/**
 * Return true, if there is Cauchy-Schwarz inequality 
 * between `fvector` and `svector`, otherwise return false.
 */
bool_t vectors_iscasc(vector_t fvector, vector_t svector)
{
   double feq, seq, teq;

   if (fvector.dim != svector.dim)
      return false;

   feq = vectors_dot_mul(fvector, svector);
   seq = vectors_dot_mul(svector, svector);
   teq = vectors_dot_mul(fvector, svector);
   if (teq < 0)
      teq *= -1;

   return (feq * seq >= teq) ? true : false;
}

/**
 * Return true, if there is Triangular inequality, between `fvector` 
 * and `svector`, otherwise return false.
 */
bool_t vectors_istriangle(vector_t fvector, vector_t svector)
{
   if (fvector.dim != svector.dim)
      return false;

   return (vectors_lenght(fvector) + vectors_lenght(svector) >=
      vectors_lenght(vectors_add(fvector, svector))) ? true : false;
}

/**
 * Return true, if there is Pythagorean inequality between `fvector` and `svector`,
 *  otherwise return false.
 */
bool_t vectors_ispythagorean(vector_t fvector, vector_t svector)
{
   if (fvector.dim != svector.dim)
      return false;

   return (pow(vectors_lenght(fvector), 2) + pow(vectors_lenght(svector), 2) == 
           pow(vectors_lenght(vectors_add(fvector, svector)), 2)) ? true : false;
}

/**
 * Return true, if `fvector` and `svector` are perpendicular, 
 * otherwise return false.
 */
bool_t vectors_isstep(vector_t fvector, vector_t svector)
{
   return vectors_angle(fvector, svector, "degrees") == 90.0 ? true : false;
}

/**
 * Return true, if `fvector` and `svector` are parallel, 
 * otherwise return false.
 */
bool_t vectors_isparallel(vector_t fvector, vector_t svector)
{
   return vectors_angle(fvector, svector, "degrees") == 180.0 ? true : false;
}

/**
 * Create a new zeros vector.
 */
vector_t vectors_zeros(dim_t dim)
{
   return vectors_arbitrary(0.0, dim);
}

/**
 * Create a new ones vector.
 */
vector_t vectors_ones(dim_t dim)
{
   return vectors_arbitrary(1.0, dim);
}

/**
 * Create a new arbitrary vector which contains `value`s.
 */
vector_t vectors_arbitrary(double value, dim_t dim)
{
   vector_t result;
   int i;

   result.dim = dim;
   
   for(i = 0; i < result.dim; i++)
      result.vector[i] = value;

   return result;
}

/**
 * Create a sequential vector which ranges its elements 
 * between `start` and `end`.
 */
vector_t vectors_sequential(int start, int end, dim_t dim)
{
   vector_t result;
   double step, point;
   int i;

   point = start;
   step = (double) (end - start) / (dim - 1);
   result.dim = dim;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = point, point += step;

   return result;
}

/**
 * Create a random vector which has `dim` dimension. 
 * All elements of vector will be between 0 and 1.
 */
vector_t vectors_random(dim_t dim)
{
   vector_t result;
   double fvalue, svalue;
   int i;

   result.dim = dim;
   srand((unsigned int) time(NULL));

   for (i = 0; i < result.dim; i++) {

      fvalue = rand(); svalue = rand();

      if (fvalue >= svalue)
         result.vector[i] = (svalue / fvalue);
      else
         result.vector[i] = (fvalue / svalue);
   }

   return result;
}

/**
 * Create a uniform vector that its elements range `start` and 
 * `end`. Uniform vector's dimension will be `dim` dimension.
 */
vector_t vectors_uniform(int start, int end, dim_t dim)
{
   vector_t result, vrandom;
   int index, value;
   double element;

   srand((unsigned int) time(NULL));
   result.dim = dim;
   vrandom = vectors_random(dim);
   index = 0;

   while (true) {

      value = rand() % ((end - start + 1));
      if (value % 2 == 0)
         element = vrandom.vector[index] * value;
      else 
         element = vrandom.vector[index] * value * -1.0;

      if (element >= start && element <= end)
         result.vector[index] = element, index ++;
      if (index == vrandom.dim)
         break;
   }

   return result;
}

/**
 * Create a randint vector that its elements range `start` and 
 * `end`. Uniform vector's dimension will be `dim` dimension.
 */
vector_t vectors_randint(int start, int end, dim_t dim)
{
   vector_t result, vuniform;
   int i;

   srand((unsigned int) time(NULL));
   result.dim = dim;
   vuniform = vectors_uniform(start, end, dim);

   for (i = 0; i < result.dim; i++)
      result.vector[i] = (int) vuniform.vector[i];

   return result;
}
 
/**
 * Transform certain three dimensional `vector` in which has defined in `old_corr` 
 * system into particular new `new_coor` system. Consistent coordinate systems are 
 * `cartesian`, `cylindrical` and `spherical`. Note that angles defined in 
 * clyndrical and speherical systems are in form of degrees. 
 */
vector_t vectors_transform(vector_t vector, str_t old_coor, str_t new_coor)
{
   vector_t result; 

   if (vector.dim != 3)
      raise_error("Vector must be three-dimensional");

   if (!strcmp(old_coor, "cartesian") && !strcmp(new_coor, "cartesian")) {
      memcpy(&result, &vector, sizeof(vector));
   } 
   else if (!strcmp(old_coor, "cartesian") && !strcmp(new_coor, "cylindrical")) {
      result.vector[0] = sqrt(pow(vector.vector[0],2) + pow(vector.vector[1],2));
      result.vector[1] = DEG(vector.vector[1] / vector.vector[0]);
      result.vector[2] = vector.vector[2];
   }
   else if (!strcmp(old_coor, "cartesian") && !strcmp(new_coor, "spherical")) {
      result.vector[0] = sqrt(pow(vector.vector[0],2) + pow(vector.vector[1],2) +
                              pow(vector.vector[2],2));
      result.vector[1] = DEG(acos(vector.vector[2] / result.vector[0]));
      result.vector[2] = DEG(atan(vector.vector[1] / vector.vector[0]));
   }
   else if (!strcmp(old_coor, "cylindrical") && !strcmp(new_coor, "cartesian")) {
      result.vector[0] = vector.vector[0] * cos(RAD(vector.vector[1]));
      result.vector[1] = vector.vector[0] * sin(RAD(vector.vector[1]));
      result.vector[2] = vector.vector[2];
   }
   else if (!strcmp(old_coor, "cylindrical") && !strcmp(new_coor, "cylindrical")) {
      memcpy(&result, &vector, sizeof(vector));
   }
   else if (!strcmp(old_coor, "cylindrical") && !strcmp(new_coor, "spherical")) {
      result.vector[0] = sqrt(pow(vector.vector[0],2) + pow(vector.vector[2],2));
      result.vector[1] = DEG(atan(result.vector[0] / vector.vector[2]));
      result.vector[2] = vector.vector[1];
   }
   else if (!strcmp(old_coor, "spherical") && !strcmp(new_coor, "cartesian")) {
      result.vector[0] = vector.vector[0] * sin(RAD(vector.vector[1])) * 
                         cos(RAD(vector.vector[2]));
      result.vector[1] = vector.vector[0] * sin(RAD(vector.vector[1])) * 
                         sin(RAD(vector.vector[2]));
      result.vector[2] = vector.vector[0] * 
                         cos(RAD(vector.vector[1]));
   }
   else if (!strcmp(old_coor, "spherical") && !strcmp(new_coor, "cylidrical")) {
      result.vector[0] = vector.vector[0] * sin(RAD(vector.vector[1]));
      result.vector[1] = vector.vector[2];
      result.vector[2] = vector.vector[0] * cos(RAD(vector.vector[1]));
   }
   else if (!strcmp(old_coor, "spherical") && !strcmp(new_coor, "spherical")) {
      memcpy(&result, &vector, sizeof(vector));
   }
   else 
      raise_error("'old_coor' and `new_coor` must be 'cartesian', "
                     "'cylindrical' or `spherical`");

   return result;
}

/**
 * Calculate the lenght of `vector` that defined 
 * in cartesian coordinate system.
 */
double vectors_lenght(vector_t vector)
{
   double res;
   int i;

   res = 0;

   for (i = 0; i < vector.dim; i ++)
      res += pow(vector.vector[i], 2);

   return sqrt(res);
}

/**
 * Calculate the absolute vector of `vector`
 * which defined in cartesian coordinate system.
 */
vector_t vectors_abs(vector_t vector)
{
   vector_t result;
   int i;

   result.dim = vector.dim;

   for (i = 0; i < result.dim; i++) {
      if (vector.vector[i] < 0)
         result.vector[i] = -1 * vector.vector[i];
      else
         result.vector[i] = vector.vector[i];
   }

   return result;
}

/**
 * Get the `n`.th power pf `vector` which defined in cartesian
 * coordinate system.
 */
vector_t vectors_pow(vector_t vector, double n)
{
   vector_t result;
   int i;

   result.dim = vector.dim;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = pow(vector.vector[i], n);

   return result;
}

/**
 * Get the `n`.th root of `vector` which defined in cartesian
 * coordinate system.
 */
vector_t vectors_root(vector_t vector, double n)
{
   vector_t result;
   int i;

   result.dim = vector.dim;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = pow(vector.vector[i], (double) 1 / 2);

   return result;
}

/**
 * Extract the unit vector from `vector` which defined in cartesian
 * coordinate system.
 */
vector_t vectors_unit(vector_t vector)
{
   vector_t result;
   int i;

   result.dim = vector.dim;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = vector.vector[i] * (1 / vectors_lenght(vector));

   return result;
}

/**
 * Add the `fvector` and `svector` which defined in cartesian
 * coordinate systems with each other.
 */
vector_t vectors_add(vector_t fvector, vector_t svector)
{
   vector_t result;
   int i;

   if (fvector.dim != svector.dim) 
      raise_error("Dimension mismatch found");

   result.dim = fvector.dim;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = fvector.vector[i] + svector.vector[i];

   return result;
}

/**
 * Subtract the `svector` from `fvector` which defined in 
 * cartesian coordinate systems with each other.
 */
vector_t vectors_subtract(vector_t fvector, vector_t svector)
{
   vector_t result;
   int i;

   if (fvector.dim != svector.dim) 
      raise_error("Dimension mismatch found");

   result.dim = fvector.dim;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = fvector.vector[i] - svector.vector[i];

   return result;
}

/**
 * Multiply the `vector` which defined in cartesian coordinate
 * system with `scaler`.
 */
vector_t vectors_scaler_mul(vector_t vector, double scaler)
{
   vector_t result;
   int i;

   result.dim = vector.dim;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = vector.vector[i] * scaler;

   return result;
}

/**
 * Measure the distance between 'fvector' and 'svector' which
 * defined in cartesian coordinate systems.
 */
double vectors_distance(vector_t fvector, vector_t svector)
{
   double distances;
   int i;

   if (fvector.dim != svector.dim) 
      raise_error("Dimension dismatch found");

   distances = 0;

   for (i = 0; i < fvector.dim; i++)
      distances += pow((fvector.vector[i] - svector.vector[i]), 2);

   return sqrt(distances);
}

/** 
 * Multiply the `fvector` and `svector` in which defined in 
 * cartesian coordinate systems as dot.  
 */
double vectors_dot_mul(vector_t fvector, vector_t svector)
{
   double multipled;
   int i;

   if (fvector.dim != svector.dim) 
      raise_error("Dimension dismatch found");

   multipled = 0;

   for (i = 0; i < fvector.dim; i++)
      multipled += fvector.vector[i] * svector.vector[i];

   return multipled;
}

/**
 * Multiply the `fvector` and `svector` in which defined in cartesian 
 * coordinate systems as cross.  
 */
vector_t vectors_cross_mul(vector_t fvector, vector_t svector)
{
   vector_t result;
   double matrix[3][3];
   int i;

   if (fvector.dim != 3 || svector.dim != 3)
      raise_error("'fvector' and 'svector' must be three-dimensional");
   
   result.dim = 3;

   // Convert the vectors to 3x3 matrix.
   for (i = 0; i < result.dim; i++) {
      matrix[0][i] = 1.0;
      matrix[1][i] = fvector.vector[i];
      matrix[2][i] = svector.vector[i];
   }

   // Find the cofactor of 'matrix' and adjust the 'result'.
   result.vector[0] = matrix[1][1]*matrix[2][2]-matrix[1][2]*matrix[2][1];
   result.vector[1] = -1.0*(matrix[1][0]*matrix[2][2]-matrix[2][0] *
                      matrix[1][2]);
   result.vector[2] = matrix[1][0]*matrix[2][1]-matrix[2][0]*matrix[1][1];

   return result;
}

/**
 * Calculate the angle between `fvector` and `svector` in which defined
 * in cartesian coordinate systems. `form` indicates the output form of
 * angle and must be one of `decimal`, `radians` or `degrees`.
 */
double vectors_angle(vector_t fvector, vector_t svector, str_t form)
{
   double fpow, spow, muled;
   float angle;
   int i;

   if (vectors_iszeros(fvector) || vectors_iszeros(svector))
      raise_error("'fvector' and 'svector' must be non-zero");

   if (fvector.dim != svector.dim)
      raise_error("Dimension dismatch found");

   angle = 0, fpow = 0, spow = 0, muled = 0;

   // Calculate the angle in form of radians.
   muled = vectors_dot_mul(fvector, svector);
   for (i = 0; i < fvector.dim; i++)
      fpow += pow(fvector.vector[i], 2);
   for (i = 0; i < svector.dim; i++)
      spow += pow(svector.vector[i], 2);

   angle = muled / (sqrt(fpow) * sqrt(spow));

   // Return the angle in form of 'form'.
   if (!strcmp(form, "decimal"))
      return angle;
   else if (!strcmp(form, "radians"))
      return acos(angle);
   else if (!strcmp(form, "degrees"))
      return DEG(acos(angle));
   else
      raise_error("'form' must be one of 'decimal', 'radians' or 'degrees'");
}
