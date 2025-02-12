/* Vector operations in ALAT (Advanced Linear Algebra Toolkit) */

#include "./alat.h"

/**
 * Transform the `vector` in one coordinate to another coordinate. `coor` must 
 * be `cartesian`, `cylindrical` or `spherical`. For `cartesian` coordinate 
 * system, there is no restriction about vector dimension. In `cylindrical` and 
 * `spherical` coordinate systems, vectors must be defined as three dimension. 
 */
vector_t alat_vector_transform(vector_t vector, coor_t coor)
{
   int i;
   vector_t result; 

   assert_vector(vector);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   result.coor = coor;
   if (vector.coor == cartesian && coor == cartesian) {
      result.dim = vector.dim;
      for (i = 0; i < result.dim; i++)
         result.vector[i] = vector.vector[i];
   }
   else if (vector.coor == cartesian && coor == cylindrical) {
      result.dim = 3;
      result.vector[0] = sqrt(pow(vector.vector[0],2) + pow(vector.vector[1],2)),
      result.vector[1] = DEG(atan(vector.vector[1] / vector.vector[0])),
      result.vector[2] = vector.vector[2];
   }
   else if (vector.coor == cartesian && coor == spherical) {
      result.dim = 3;
      result.vector[0] = sqrt(pow(vector.vector[0],2) + pow(vector.vector[1],2) +
                              pow(vector.vector[2],2));
      result.vector[1] = DEG(acos(vector.vector[2] / result.vector[0]));
      result.vector[2] = DEG(atan(vector.vector[1] / vector.vector[0]));
   }
   else if (vector.coor == cylindrical && coor == cartesian) {
      result.dim = 3;
      result.vector[0] = vector.vector[0] * cos(RAD(vector.vector[1]));
      result.vector[1] = vector.vector[0] * sin(RAD(vector.vector[1]));
      result.vector[2] = vector.vector[2];
   }
   else if (vector.coor == cylindrical && coor == cylindrical) {
      result.dim = 3;
      for (i = 0; i < result.dim; i++)
         result.vector[i] = vector.vector[i];
   }
   else if (vector.coor == cylindrical && coor == spherical) {
      result.dim = 3;
      result.vector[0] = sqrt(pow(vector.vector[0],2) + pow(vector.vector[2],2));
      result.vector[1] = DEG(atan(vector.vector[0] / vector.vector[2]));
      result.vector[2] = vector.vector[1];
   }
   else if (vector.coor == spherical && coor == cartesian) {
      result.dim = 3;
      result.vector[0] = vector.vector[0] * sin(RAD(vector.vector[1])) * 
                         cos(RAD(vector.vector[2]));
      result.vector[1] = vector.vector[0] * sin(RAD(vector.vector[1])) * 
                         sin(RAD(vector.vector[2]));
      result.vector[2] = vector.vector[0] * cos(RAD(vector.vector[1]));
   }
   else if (vector.coor == spherical && coor == cylindrical) {
      result.dim = 3;
      result.vector[0] = vector.vector[0] * sin(RAD(vector.vector[1]));
      result.vector[1] = vector.vector[2];
      result.vector[2] = vector.vector[0] * cos(RAD(vector.vector[1]));
   }
   else {
      result.dim = 3;
      for (i = 0; i < result.dim; i++)
         result.vector[i] = vector.vector[i];
   }
      
   return result;
}

/**
 * Return `true`, if `vector` is defined in cartesian
 * coordinate, otherwise return `false`.
 */
bool_t alat_vector_iscartesian(vector_t vector)
{
   assert_vector(vector);
   
   return (vector.coor == cartesian) ? true : false;
}

/**
 * Return `true`, if `vector` is defined in cylindrical
 * coordinate, otherwise return `false`.
 */
bool_t alat_vector_iscylindrical(vector_t vector)
{
   assert_vector(vector);

   return (vector.coor == cylindrical) ? true : false;
}

/**
 * Return `true`, if `vector` is defined in spherical
 * coordinate, otherwise return `false`.
 */
bool_t alat_vector_isspherical(vector_t vector)
{
   assert_vector(vector);

   return (vector.coor == spherical) ? true : false;
}

/**
 * Return `true` if `vector` just contains zeros, 
 * otherwise return `false`.
 */
bool_t alat_vector_iszeros(vector_t vector)
{
   return alat_vector_isarbitrary(vector, 0.0);
}

/**
 * Return `true` if `vector` just contains ones, 
 * otherwise return `false`.
 */
bool_t alat_vector_isones(vector_t vector)
{
   return alat_vector_isarbitrary(vector, 1.0);
}

/**
 * Return `true` if `vector` just contains `value`s, otherwise
 * return `false`.
 */
bool_t alat_vector_isarbitrary(vector_t vector, double value)
{
   int i;

   assert_vector(vector);

   vector = alat_vector_transform(vector, cartesian); 

   for (i = 0; i < vector.dim; i++)
      if (vector.vector[i] != value)
         return false;

   return true;
} 

/**
 * Return `true`, if `fvector` and `svector` are equal, otherwise
 * return `false`.
 */
bool_t alat_vector_isequal(vector_t fvector, vector_t svector)
{
   int i;

   assert_vector(fvector);
   assert_vector(svector);

   fvector = alat_vector_transform(fvector, cartesian);
   svector = alat_vector_transform(svector, cartesian);

   if (fvector.dim != svector.dim)
      return false;
   for (i = 0; i < fvector.dim; i++)
      if (fvector.vector[i] != svector.vector[i])
         return false;

   return true;
}

/**
 * Return `true`, if there is Cauchy-Schwarz inequality 
 * between `fvector` and `svector`, otherwise return `false`.
 */
bool_t alat_vector_iscasc(vector_t fvector, vector_t svector)
{
   double feq, seq, teq;

   assert_vector(fvector);
   assert_vector(svector);

   fvector = alat_vector_transform(fvector, cartesian);
   svector = alat_vector_transform(svector, cartesian);

   if (fvector.dim != svector.dim)
      return false;
   feq = alat_vector_dot_mul(fvector, svector);
   seq = alat_vector_dot_mul(svector, svector);
   teq = alat_vector_dot_mul(fvector, svector);
   if (teq < 0)
      teq *= -1;

   return (feq * seq >= teq) ? true : false;
}

/**
 * Return `true`, if there is Triangular inequality between `fvector` 
 * and `svector`, otherwise return `false`.
 */
bool_t alat_vector_istriangle(vector_t fvector, vector_t svector)
{
   return (alat_vector_lenght(fvector) + alat_vector_lenght(svector) >=
      alat_vector_lenght(alat_vector_add(fvector, svector, cartesian))) 
      ? true : false;
}

/**
 * Return `true`, if there is Pythagorean inequality between `fvector` 
 * and `svector`, otherwise return `false`.
 */
bool_t alat_vector_ispythagorean(vector_t fvector, vector_t svector)
{
   return (pow(alat_vector_lenght(fvector), 2) + pow(alat_vector_lenght(svector), 2) 
      == pow(alat_vector_lenght(alat_vector_add(fvector, svector, cartesian)), 2)) 
      ? true : false;
}

/**
 * Return `true`, if `fvector` and `svector` are perpendicular, 
 * otherwise return `false`.
 */
bool_t alat_vector_issteep(vector_t fvector, vector_t svector)
{
   return alat_vector_angle(fvector, svector, degrees) == 90.0 ? true : false;
}

/**
 * Return `true`, if `fvector` and `svector` are parallel, 
 * otherwise return `false`.
 */
bool_t alat_vector_isparallel(vector_t fvector, vector_t svector)
{
   return alat_vector_angle(fvector, svector, degrees) == 180.0 ? true : false;
}

/**
 * Return the `n`.th axis of `vector`. If `vector` is 
 * not defined in cartesian coordinate, convert it.
 */
double alat_vector_car_n(vector_t vector, int n)
{
   assert_vector(vector);
   assert (n >= 0 && n < vector.dim);

   return alat_vector_transform(vector, cartesian).vector[n];
}

/**
 * Return the x axis of `vector`. If `vector` is 
 * not defined in cartesian coordinate, convert it.
 */
double alat_vector_car_x(vector_t vector)
{
   return alat_vector_car_n(vector, 0);
}

/**
 * Return the y axis of `vector`. If `vector` is 
 * not defined in cartesian coordinate, convert it.
 */
double alat_vector_car_y(vector_t vector)
{
   return alat_vector_car_n(vector, 1);
}

/**
 * Return the z axis of `vector`. If `vector` is 
 * not defined in cartesian coordinate, convert it.
 */
double alat_vector_car_z(vector_t vector)
{
   return alat_vector_car_n(vector, 2);
}

/**
 * Return the radial axis of `vector`. If `vector` is 
 * not defined in cylindrical coordinate, convert it.
 */
double alat_vector_cyl_radial(vector_t vector)
{
   return alat_vector_transform(vector, cylindrical).vector[0];
}

/**
 * Return the angular axis of `vector`. If `vector` is 
 * not defined in cylindrical coordinate, convert it.
 */
double alat_vector_cyl_angular(vector_t vector)
{
   return alat_vector_transform(vector, cylindrical).vector[1];
}

/**
 * Return the z axis of `vector`. If `vector` is 
 * not defined in cylindrical coordinate, convert it.
 */
double alat_vector_cyl_z(vector_t vector)
{
   return alat_vector_transform(vector, cylindrical).vector[2];
}

/**
 * Return the radial axis of `vector`. If `vector` is 
 * not defined in spherical coordinate, convert it.
 */
double alat_vector_sph_radial(vector_t vector)
{
   return alat_vector_transform(vector, spherical).vector[0];
}

/**
 * Return the polar axis of `vector`. If `vector` is 
 * not defined in spherical coordinate, convert it.
 */
double alat_vector_sph_polar(vector_t vector)
{
   return alat_vector_transform(vector, spherical).vector[1];
}

/**
 * Return the azimuthal axis of `vector`. If `vector` 
 * is not defined in spherical coordinate, convert it.
 */
double alat_vector_sph_azimuthal(vector_t vector)
{
   return alat_vector_transform(vector, spherical).vector[2];
}


/**
 * Create zeros vector which will be had `dim` and
 * defined in `coor`.
 */
vector_t alat_vector_zeros(dim_t dim, coor_t coor)
{
   return alat_vector_arbitrary(0.0, dim, coor);
}

/**
 * Create ones vector which will be had `dim` and
 * defined in `coor`.
 */
vector_t alat_vector_ones(dim_t dim, coor_t coor)
{
   return alat_vector_arbitrary(1.0, dim, coor);
}

/**
 * Create zeros vector which will be had `dim`, contained `values`s and
 * defined in `coor`.
 */
vector_t alat_vector_arbitrary(double value, dim_t dim, coor_t coor)
{
   int i;
   vector_t result;

   assert (dim > 0 && dim <= MAX_DIM);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   result.dim = dim;
   result.coor = cartesian;
   for (i = 0; i < result.dim; i++)
      result.vector[i] = value;

   return alat_vector_transform(result, coor);
}

/**
 * Create sequential vector which ranges between `start` and `end`, has `dim`,
 * and defined in `coor`.
 */
vector_t alat_vector_sequential(double start, double end, dim_t dim, coor_t coor)
{
   int i;
   double step, point;
   vector_t result;

   assert (dim > 0 && dim <= MAX_DIM);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   point = start;
   step = (double) (end - start) / (dim - 1);
   result.dim = dim;
   result.coor = cartesian;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = point, point += step;
   
   return alat_vector_transform(result, coor);
}

/**
 * Create random vector which ranges between 0 and 1, has 
 * `dim`, and defined in `coor`.
 */
vector_t alat_vector_random(dim_t dim, coor_t coor)
{
   int i;
   double fvalue, svalue;
   vector_t result;

   assert (dim > 0 && dim <= MAX_DIM);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);
   
   result.dim = dim;
   result.coor = cartesian;
   srand((unsigned int) time(NULL));

   for (i = 0; i < result.dim; i++) {
      fvalue = rand(); 
      svalue = rand();
      if (fvalue >= svalue)
         result.vector[i] = (svalue / fvalue);
      else
         result.vector[i] = (fvalue / svalue);
   }
   return alat_vector_transform(result, coor);
}

/**
 * Create uniform vector which ranges between `start` and `end`, has `dim` and
 * defined in `coor`.
 */
vector_t alat_vector_uniform(int start, int end, dim_t dim, coor_t coor)
{
   int index, value;
   double axis;
   vector_t result;

   assert (dim > 0 && dim <= MAX_DIM);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   result = alat_vector_random(dim, cartesian);
   index = 0;

   while (true) {
      value = rand() % (end - start + 1);
      if (value % 2 == 0)
         axis = result.vector[index] * value * 1.0;
      else 
         axis = result.vector[index] * value * -1.0;
      if (axis >= start && axis <= end)
         result.vector[index] = axis, index ++;
      if (index == result.dim)
         break;
   }
   return alat_vector_transform(result, coor);
}

/**
 * Create randint vector which ranges between `start` and `end`, has `dim`, and
 * defined in `coor`.
 */
vector_t alat_vector_randint(int start, int end, dim_t dim, coor_t coor)
{
   int i;
   vector_t result;

   assert (dim > 0 && dim <= MAX_DIM);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   result = alat_vector_uniform(start, end, dim, cartesian);
   for (i = 0; i < result.dim; i++)
      result.vector[i] = (int) result.vector[i];

   return alat_vector_transform(result, coor);
}

/**
 * Return the dimension of `vector`.
 */
dim_t alat_vector_dim(vector_t vector)
{
   assert_vector(vector);

   return vector.dim;
}

/**
 * Return the coordinate system of `vector`.
 */
coor_t alat_vector_coor(vector_t vector)
{
   assert_vector(vector);

   return vector.coor;
}

/**
 * Calculate the lenght of `vector`.
 */
double alat_vector_lenght(vector_t vector)
{
   int i;
   double result;

   assert_vector(vector);

   result = 0;
   vector = alat_vector_transform(vector, cartesian);

   for (i = 0; i < vector.dim; i ++)
      result += pow(vector.vector[i], 2);

   return sqrt(result);
}

/**
 * Calculate the magnitude of `vector`.
 */
double alat_vector_magnitude(vector_t vector)
{
   int i;
   double result;

   assert_vector(vector);

   result = 0;
   vector = alat_vector_transform(vector, cartesian);

   for (i = 0; i < vector.dim; i++)
      result += pow(vector.vector[i], 2.0);

   return sqrt(result);
}

/**
 * Return the absolute `vector` which defined in `coor`.
 */
vector_t alat_vector_abs(vector_t vector, coor_t coor)
{
   int i;
   vector_t result;

   assert_vector(vector);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);
   
   vector = alat_vector_transform(vector, cartesian);
   result.dim = vector.dim;
   result.coor = cartesian;

   for (i = 0; i < result.dim; i++) {
      if (vector.vector[i] < 0)
         result.vector[i] = -1 * vector.vector[i];
      else
         result.vector[i] = vector.vector[i];
   }
   return alat_vector_transform(result, coor);
}

/**
 * Get `n`.th power of `vector` which will be defined in `coor`.
 */
vector_t alat_vector_pow(vector_t vector, double n, coor_t coor)
{
   int i;
   vector_t result;

   assert_vector(vector);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   vector = alat_vector_transform(vector, cartesian);
   result.dim = vector.dim;
   result.coor = cartesian;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = pow(vector.vector[i], n);

   return alat_vector_transform(result, coor);
} 

/**
 * Get `n`.th root of `vector` which will be defined in `coor`.
 */
vector_t alat_vector_root(vector_t vector, double n, coor_t coor)
{
   int i;
   vector_t result;

   assert_vector(vector);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   vector = alat_vector_transform(vector, cartesian);
   result.dim = vector.dim;
   result.coor = cartesian;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = pow(vector.vector[i], 1.0 / n);

   return alat_vector_transform(result, coor);
}

/**
 * Get square root of `vector` which will be defined in `coor`.
 */
vector_t alat_vector_sqrt(vector_t vector, coor_t coor)
{
   return alat_vector_root(vector, 2, coor);
}

/**
 * Extract the unit vector from `vector` which will be defined 
 * in `cartesian`.
 */
vector_t alat_vector_unit(vector_t vector, coor_t coor)
{
   int i;
   vector_t result;

   assert_vector(vector);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   vector = alat_vector_transform(vector, cartesian);
   result.dim = vector.dim;
   result.coor = cartesian;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = vector.vector[i] * (1 / alat_vector_lenght(vector));

   return alat_vector_transform(result, coor);
}

/**
 * Add the `fvector` and `svector` which will be defined in `coor`.
 */
vector_t alat_vector_add(vector_t fvector, vector_t svector, coor_t coor)
{
   int i;
   vector_t result;

   assert_vector(fvector);
   assert_vector(svector);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   fvector = alat_vector_transform(fvector, cartesian);
   svector = alat_vector_transform(svector, cartesian);

   assert (fvector.dim == svector.dim);  

   result.dim = fvector.dim;
   result.coor = cartesian; 

   for (i = 0; i < result.dim; i++)
      result.vector[i] = fvector.vector[i] + svector.vector[i];

   return alat_vector_transform(result, coor);
}

/**
 * Multiply the `vector` by `scalar` which will be defined in `coor`.
 */
vector_t alat_vector_scalar_mul(vector_t vector, double scalar, coor_t coor)
{
   int i;
   vector_t result;

   assert_vector(vector);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   vector = alat_vector_transform(vector, cartesian);
   result.dim = vector.dim;
   result.coor = cartesian;

   for (i = 0; i < result.dim; i++)
      result.vector[i] = vector.vector[i] * scalar;

   return alat_vector_transform(result, coor);
}

/**
 * Subtract the `svector` from `fvector` which will be defined in `coor`.
 */
vector_t alat_vector_sub(vector_t fvector, vector_t svector, coor_t coor)
{
   return alat_vector_add(fvector, alat_vector_scalar_mul(svector, -1.0, cartesian), coor);
}

/**
 * Measure the distance between 'fvector' and 'svector' which
 * defined in cartesian coordinate systems.
 */
double alat_vector_distance(vector_t fvector, vector_t svector)
{
   int i;
   double distances;

   assert_vector(fvector);
   assert_vector(svector);

   fvector = alat_vector_transform(fvector, cartesian);
   svector = alat_vector_transform(svector, cartesian);

   assert (fvector.dim == svector.dim);

   distances = 0;
   for (i = 0; i < fvector.dim; i++)
      distances += pow((fvector.vector[i] - svector.vector[i]), 2);

   return sqrt(distances);
}

/** 
 * Multiply the `fvector` and `svector` with each other as dot.
 */
double alat_vector_dot_mul(vector_t fvector, vector_t svector)
{
   int i;
   double result;

   assert_vector(fvector);
   assert_vector(svector);

   fvector = alat_vector_transform(fvector, cartesian);
   svector = alat_vector_transform(svector, cartesian);

   assert (fvector.dim == svector.dim);

   result = 0;
   for (i = 0; i < fvector.dim; i++)
      result += fvector.vector[i] * svector.vector[i];

   return result;
}

/**
 * Multiply the `fvector` and `svector` with each other as cross.  
 */
vector_t alat_vector_cross_mul(vector_t fvector, vector_t svector, coor_t coor)
{
   int i;
   double matrix[3][3];
   vector_t result;

   assert_vector(fvector);
   assert_vector(svector);
   assert (coor == cartesian || coor == cylindrical || coor == spherical);

   fvector = alat_vector_transform(fvector, cartesian);
   svector = alat_vector_transform(svector, cartesian);
   result.dim = 3;
   result.coor = cartesian;

   for (i = 0; i < result.dim; i++) 
      matrix[0][i] = 1.0, matrix[1][i] = fvector.vector[i], 
      matrix[2][i] = svector.vector[i];
   result.vector[0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
   result.vector[1] = -1.0 * (matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]);
   result.vector[2] = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];

   return alat_vector_transform(result, coor);
}

/**
 * Project the `fvector` onto `svector` which will be defined in `coor`.
 */
vector_t alat_vector_project(vector_t fvector, vector_t svector, coor_t coor)
{
   return alat_vector_scalar_mul(svector, alat_vector_dot_mul(fvector, svector) / 
      alat_vector_dot_mul(svector, svector), coor);
}

/**
 * Reflect the `fvector` onto `svector` which will be defined in `coor`.
 */
vector_t alat_vector_reflect(vector_t fvector, vector_t svector, coor_t coor)
{
   return alat_vector_sub(fvector, alat_vector_scalar_mul(
      alat_vector_project(fvector, svector, cartesian), 2.0, cartesian), coor);
}

/**
 * Interpolate the `fvector` and `svector` with each other which will be defined in `coor`.
 * `factor` must range between 0 and 1.
 */
vector_t alat_vector_interpolate(vector_t fvector, vector_t svector, double factor, coor_t coor)
{
   assert (factor >= 0.0 && factor <= 1.0);

   return alat_vector_add(alat_vector_scalar_mul(fvector, 1 - factor, cartesian), 
      alat_vector_scalar_mul(svector, factor, cartesian), coor);
}

/**
 * Return the angle between `fvector` and `svector`. `form` indicates the 
 * output form of angle and must be one of `decimal`, `radians` or `degrees`.
 */
double alat_vector_angle(vector_t fvector, vector_t svector, form_t form)
{
   int i;
   double fpow, spow, muled;
   float angle;

   assert_vector(fvector);
   assert_vector(svector);
   assert (form == decimal || form == radians || form == degrees);
   assert (!alat_vector_iszeros(fvector) && !alat_vector_iszeros(svector));

   fvector = alat_vector_transform(fvector, cartesian);
   svector = alat_vector_transform(svector, cartesian);

   assert (fvector.dim == svector.dim);

   angle = 0, fpow = 0, spow = 0, muled = 0;
   muled = alat_vector_dot_mul(fvector, svector);

   for (i = 0; i < fvector.dim; i++)
      fpow += pow(fvector.vector[i], 2);
   for (i = 0; i < svector.dim; i++)
      spow += pow(svector.vector[i], 2);

   angle = muled / (sqrt(fpow) * sqrt(spow));

   return (form == decimal) ? angle : (form == radians) ? acos(angle) :
          DEG(acos(angle));
}
