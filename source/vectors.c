/*  Vector Operations in ALAT (Advanced Linear Algebra Toolkit)  */

#include "../include/vectors.h"

/* --------------------------------------------------------------- */
/* ----------------------- Helper Functions  --------------------- */
/* --------------------------------------------------------------- */

/** @brief Display the 'vector' vector.
 *  @param vector Vector object that will be displayed.
 *  @return `void` object. 
*/
void __display_vector__(vector_t vector) {
   // Display the dimension of 'vector_t' object.
   printf("Dimension : %d\n", vector.dim);
   // Display the coordinate system of 'vector_t' object.
   if (vector.coor == CARTESIAN)
      printf("Coordinate: CARTESIAN\n");
   else if (vector.coor == CYLINDRICAL)
      printf("Coordinate: CYLINDRICAL\n");
   else 
      printf("Coordinate: SPHERICAL\n");
   // Display the vector of 'vector_t' object.
   printf("Vector    : ");
   for (int i=0; i<vector.dim; i++)
      printf("%f ", vector.vector[i]);
   printf("\n");
}

/* --------------------------------------------------------------- */
/* ------------------------ Main Functions ----------------------- */
/* --------------------------------------------------------------- */

/** @brief Transform the location of a point in one coordinate 
 *         system to another coordinate system using `coordinate`.
 *  @param vector Vector that will be transformed.
 *  @param coordinate The new coordinate system. This parameter 
 *                    must be one of the @ref `coor_t` object.
 * @return `vector_t` object.
 */
vector_t transform(vector_t vector, coor_t coordinate) {
   // To make this transformation, 'vector' vector must 
   // be three dimensional.
   assert ((vector.dim == 3) &&  
           (coordinate == CARTESIAN || 
            coordinate == CYLINDRICAL ||
            coordinate == SPHERICAL));
   // Indicate the local variable/s and set its properties.
   vector_t result;
   result.dim = 3, result.coor = coordinate;
   // Transform the CARTESIAN coordinate system to anothers.
   if (vector.coor == CARTESIAN)
      if (coordinate == CARTESIAN)
         result.vector[0] = vector.vector[0], 
         result.vector[1] = vector.vector[1], 
         result.vector[2] = vector.vector[2];
      else if (coordinate == CYLINDRICAL)
         result.vector[0] = sqrt(pow(vector.vector[0], 2) +
                                 pow(vector.vector[1], 2)), 
         result.vector[1] = DEG(vector.vector[1] / 
                                vector.vector[0]), 
         result.vector[2] = vector.vector[2];
      else
         result.vector[0] = sqrt(pow(vector.vector[0], 2) + 
                                 pow(vector.vector[1], 2) +
                                 pow(vector.vector[2], 2)), 
         result.vector[1] = DEG(acos(vector.vector[2] /
                                result.vector[0])), 
         result.vector[2] = DEG(atan(vector.vector[1] /
                                vector.vector[0]));
   // Transform the CYLINDRICAL coordinate system to anothers.
   else if (vector.coor == CYLINDRICAL)
      if (coordinate == CARTESIAN)
         result.vector[0] = vector.vector[0] * cos(
                                       RAD(vector.vector[1])), 
         result.vector[1] = vector.vector[0] * sin(
                                       RAD(vector.vector[1])), 
         result.vector[2] = vector.vector[2];
      else if (coordinate == CYLINDRICAL)
         result.vector[0] = vector.vector[0],   
         result.vector[1] = vector.vector[1],   
         result.vector[2] = vector.vector[2];   
      else
         result.vector[0] = sqrt(pow(vector.vector[0], 2) + 
                                 pow(vector.vector[2], 2)), 
         result.vector[1] = DEG(atan(result.vector[0] / 
                                     vector.vector[2])), 
         result.vector[2] = vector.vector[1];
   // Transform the SPHERICAL coordinate system to anothers.
   else
      if (coordinate == CARTESIAN) 
         result.vector[0] = vector.vector[0] * 
                            sin(RAD(vector.vector[1])) * 
                            cos(RAD(vector.vector[2])), 
         result.vector[1] = vector.vector[0] * 
                            sin(RAD(vector.vector[1])) * 
                            sin(RAD(vector.vector[2])), 
         result.vector[2] = vector.vector[0] * 
                            cos(RAD(vector.vector[1]));
      else if (coordinate == CYLINDRICAL)
         result.vector[0] = vector.vector[0] * 
                            sin(RAD(vector.vector[1])), 
         result.vector[1] = vector.vector[2], 
         result.vector[2] = vector.vector[0] * 
                            cos(RAD(vector.vector[1]));
      else
         result.vector[0] = vector.vector[0], 
         result.vector[1] = vector.vector[1], 
         result.vector[2] = vector.vector[2];

   return result;
}

/** @brief Calculate the lenght of 'vector' vector. 
 *  @param vector Vector object that will be calculated.
 *  @return `double` object.
 */
double lenght(vector_t vector) {
   // Check that 'vector' is in cartesian coordinate.
   assert (vector.coor == CARTESIAN);
   // Indicate the local variable/s.
   double pows = 0;
   // Gather the all powers of elements of 'vector'.
   for (int i=0; i<vector.dim; i++)
      pows += pow(vector.vector[i], 2);

   return sqrt(pows);
}

/** @brief Return true, if 'vector1' vector and 'vector2' 
 *         vector are same, otherwise, return false.
 *  @param vector1 First vector_t object that will be checked.
 *  @param vector2 Second vector_t object that will be checked.
 *  @return `boolean` object. 
 */
boolean isequal(vector_t vector1, vector_t vector2) {
   // Check that the dimension and coordinate system of both
   // 'vector1' and 'vector2' vectors.
   if (vector1.dim != vector2.dim || vector1.coor != vector2.coor) 
      return false;
   // Check that the elemenents of vectors are equal or not.
   for (int i=0; i<vector1.dim; i++)
      if (vector1.vector[i] != vector2.vector[i])
         return false;

   return true;
}

/** @brief Return true, if 'vector' vector contains just 0s.
 *  @param vector vector_t object that will be checked.
 *  @return `boolean` object. 
 */
boolean iszeros(vector_t vector) {
   // Check the all elements of 'vector' vector.
   for (int i=0; i<vector.dim; i++)
      if (vector.vector[i] != 0.0)
         return false;

   return true;
}

/** @brief Calculate the unit vector of 'vector' vector.
 *  @param vector vector_t object that will be calculated.
 *  @return `vector_t` object. 
 */
vector_t unit(vector_t vector) {
   // Check that 'vector' is in cartesian coordinate.
   assert (vector.coor == CARTESIAN);
   // Indicate the local variable/s.
   double len;
   vector_t result;
   result.dim == vector.dim, result.coor = CARTESIAN;
   // Calculate the lenght of 'vector' vector.
   assert (len = lenght(vector)); 
   // Calculate the unit vector.
   for (int i=0; i<result.dim; i++)
      result.vector[i] = result.vector[i] * (1/len);

   return result;
}
 
/** @brief Add given 'vector1' and 'vector2' vectors.
 *  @param vector1 First vector_t object that will be added.
 *  @param vector2 Second vector_t object that will be added.
 *  @return `vector_t` object. 
 */
vector_t add(vector_t vector1, vector_t vector2) {
   // Check that there is any imcompitable between two vectors.
   assert (vector1.dim == vector2.dim);
   // Check that both vectors are in cartesian coordinates.
   assert (vector1.coor == CARTESIAN && vector2.coor == CARTESIAN);
   // Indicate the local variabe/s.
   vector_t result;
   result.dim = vector1.dim;
   result.coor = CARTESIAN;
   // Add the elements of both vectors.
   for (int i=0; i<vector1.dim; i++)
      result.vector[i] = vector1.vector[i] + vector2.vector[i];

   return result;
}

/** @brief Measures the distance between 'vector1' and 'vector2'.
 *  @param vector1 First vector that will be measured.
 *  @param vector2 Second vector that will be measured.
 *  @return `vector_t` object. 
 */
double distance(vector_t vector1, vector_t vector2) {
   // Check that there is any dimension imcompitablity.
   assert (vector1.dim == vector2.dim);
   // Check that both vectors are in cartesian coordinates.
   assert (vector1.coor == CARTESIAN && vector2.coor == CARTESIAN);
   // Indicate the local variable/s.
   double distances;
   // Measure the distance.
   for (int i=0; i<vector1.dim; i++)
      distances += pow(vector1.vector[i] - vector2.vector[i], 2);

   return sqrt(distances);
}

/** @brief Multiply the 'scaler' scaler with 'vector' vector. 
 *  @param scaler Scaler value that will multiply 'vector'.
 *  @param vector Vector that will multiplied with 'scaler'.
 *  @return `vector_t` object.
 */
vector_t scaler_mul(double scaler, vector_t vector) {
   // Check that 'vector' is in cartesian coordinate.
   assert (vector.coor == CARTESIAN);
   // Indicate the local variable/s.
   vector_t result;
   result.dim = vector.dim, result.coor = CARTESIAN;
   // Multiply the 'scaler' with 'vector'.
   for (int i=0; i<result.dim; i++)
      result.vector[i] = result.vector[i] * scaler;

   return result;
}

/** @brief Multiply the 'vector1' and 'vector2' vectors as dot. 
 *  @param vector1 First vector that will be multiplied.
 *  @param vector2 Second vector that will be multiplied.
 *  @return `double` object.
 */
double dot_mul(vector_t vector1, vector_t vector2) {
   // Check that there is any dimension imcompitablity.
   assert (vector1.dim == vector2.dim);
   // Check that both vectors are in cartesian coordinates.
   assert (vector1.coor == CARTESIAN && vector2.coor == CARTESIAN);
   // Indicate the local variable/s.
   double total = 0;
   // Multipled the vectors.
   for (int i=0; i<vector1.dim; i++)
      total += vector1.vector[i] * vector2.vector[i];

   return total;
}

/** @brief Multiply the 'vector1' and 'vector2' vectors as cross. 
 *  @param vector1 First vector that will be multiplied.
 *  @param vector2 Second vector that will be multiplied.
 *  @return `double` object.
 */
vector_t cross_mul(vector_t vector1, vector_t vector2) { 
   // Indicate the local variable/s.
   double matrix[3][3];
   vector_t result;
   result.dim = 3, result.coor = CARTESIAN;
   // Check that both vectors are in cartesian coordinates.
   assert (vector1.coor == CARTESIAN && vector2.coor == CARTESIAN);
   // Check that dimensions of vectors are three or not.
   assert (vector1.dim == 3 && vector2.dim == 3);
   // Create a 3x3 matrix and fill in it with vectors.
   for (int i=0; i<3; i++)
      matrix[0][i] = 1.0, 
      matrix[1][i] = vector1.vector[i], 
      matrix[2][i] = vector2.vector[i];
   // Create the result vector using 'matrix' elements.
   result.vector[0] = ((matrix[1][1] * matrix[2][2]) - 
                       (matrix[1][2] * matrix[2][1]));
   result.vector[1] = -1.0 * ((matrix[1][0] * matrix[2][2]) -
                              (matrix[2][0] * matrix[1][2]));
   result.vector[2] = ((matrix[1][0] * matrix[2][1]) - 
                       (matrix[2][0] * matrix[1][1]));
   return result;
}

/** @brief Return true, if there is Cauchy-Schwarz inequality, 
 *         otherwise, return false. 
 *  @param vector1 First vector that will be checked.
 *  @param vector2 Second vector that will be checked.
 *  @return `boolean` object.
 */
boolean iscs(vector_t vector1, vector_t vector2) {
   // Check that there is any dimension imcompitablity.
   if ((vector1.dim != vector2.dim) )
      return false;
   // Check that both vectors are in cartesian coordinates.
   if (vector1.coor != CARTESIAN || vector2.coor != CARTESIAN)
      return false;
   // Make some vector multiplications.
   double mul1 = dot_mul(vector1, vector2);
   double mul2 = dot_mul(vector1, vector1);
   double mul3 = dot_mul(vector2, vector2);
   // Check the Cauchy-Schwarz inequality.
   return ((mul2 * mul3) >= ((mul1 < 0) ? (mul1 * -1) : (mul1)) 
          ? true : false);
}

/** @brief Return true, if there is triangular inequality, 
 *         otherwise return false. 
 *  @param vector1 First vector that will be checked.
 *  @param vector2 Second vector that will be checked.
 *  @return `boolean` object.
 */
boolean istriangle(vector_t vector1, vector_t vector2) {
   // Check that there is any dimension imcompitablity.
   if (vector1.dim != vector2.dim)
      return false;
   // Check that both vectors are in cartesian coordinates.
   if (vector1.coor != CARTESIAN || vector2.coor != CARTESIAN)
      return false;
   // Check the triangular inequality.
   return (lenght(vector1) + lenght(vector2) >=
           lenght(add(vector1, vector2))) ? true : false;
}

/** @brief Return true, if there is pythagorean inequality, 
 *         otherwise return false. 
 *  @param vector1 First vector that will be checked.
 *  @param vector2 Second vector that will be checked.
 *  @return `boolean` object.
 */
boolean ispythag(vector_t vector1, vector_t vector2) {
   // Check that there is any dimension imcompitablity.
   if (vector1.dim != vector2.dim)
      return false;
   // Check that both vectors are in cartesian coordinates.
   if (vector1.coor != CARTESIAN || vector2.coor != CARTESIAN)
      return false;
   // Check the pythagorean inequality.
   return (pow(lenght(add(vector1, vector2)), 2) == 
           pow(lenght(vector1), 2) + pow(lenght(vector2), 2)) ?
           true : false;
}

/** @brief Calculate the angle between 'vector1' and 'vector2' vectors.
 *         The calculated angle can be in three form. These are decimal, 
 *         radians and degrees. Can be selected it via @ref `form_t` 
 *         enumeration.
 *  @param form The calculated angle form. That form can be 
 *         'DECIMAL', 'RADIANS' or 'DEGREES'. 
 *  @param vector1 First vector that will be calculated.
 *  @param vector2 Second vector that will be calculated.
 *  @return `double` object.
 */
double angle(form_t form, vector_t vector1, vector_t vector2) {
   // Check if that vectors has same dimensions or not.
   assert (vector1.dim == vector2.dim);
   // Check if that vectors are not zero vectors.
   assert (!iszeros(vector1) && !iszeros(vector2));
   // Check that 'form' has appropriate values.
   assert (form == DECIMAL || form == RADIANS || form == DEGREES);
   // Check that both vectors are in cartesian coordinates.
   assert (vector1.coor == CARTESIAN && vector2.coor == CARTESIAN);
   // Indicate the local variable/s.
   double pow1 = 0, pow2 = 0, mul = 0;
   float angle;
   // Make some vector operations.
   mul = dot_mul(vector1, vector2);
   for (int i=0; i<vector1.dim; i++)
      pow1 += pow(vector1.vector[i], 2);
   for (int i=0; i<vector2.dim; i++)
      pow2 += pow(vector2.vector[i], 2);
   angle = mul / (sqrt(pow1) * sqrt(pow2));
   // Return the angle in appriopriate form.
   if (form == DECIMAL)
      return angle;
   else if (form == RADIANS)
      return acos(angle);
   else
      return DEG(acos(angle));
}

/** @brief Return true, if 'vector1' and 'vector2' vectors are steep 
 *         with each other, otherwise return false. 
 *  @param vector1 First vector that will be checked.
 *  @param vector2 Second vector that will be checked.
 *  @return `boolean` object.
 */
boolean issteep(vector_t vector1, vector_t vector2) {
   // Check that both of vectors are steep with each other or not.
   return (angle(DEGREES, vector1, vector2) == 90.0) ? true : false;
}

/** @brief Return true, if 'vector1' and 'vector2' vectors are parallel 
 *         with each other, otherwise return false. 
 *  @param vector1 First vector that will be checked.
 *  @param vector2 Second vector that will be checked.
 *  @return `boolean` object.
 */
boolean isparallel(vector_t vector1, vector_t vector2) {
   // Check that both of vectors are paralel with each other or not.
   return (angle(DEGREES, vector1, vector2) == 180.0) ? true : false;  
}
 