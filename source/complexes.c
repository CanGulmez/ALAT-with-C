/* Complex operations in ALAT (Advanced Linear Algebra Toolkit) */

#include "../include/complexes.h"

/* --------------------------------------------------------------- */
/* ----------------------- Helper Functions  --------------------- */
/* --------------------------------------------------------------- */

void __display_complex__(complex_t complex) {
   // Display the contents of 'complex' number.
   if (complex.form == CARTESIAN)
      printf("Form          : CARTESIAN\n"), 
      printf("Complex (x, y): %f, %f\n", complex.complex[0], 
                                         complex.complex[1]);
   else if (complex.form == POLAR)
      printf("Form              : POLAR\n"), 
      printf("Complex (r, tetha): %f, %f\n", complex.complex[0], 
                                             complex.complex[1]);
}

/* --------------------------------------------------------------- */
/* ------------------------ Main Functions ----------------------- */
/* --------------------------------------------------------------- */

/** @brief Transform the 'complex' number in one form to another.
 *  @param complex Complex number that will be transformed.
 *  @param form New form of 'complex'.
 *  @return `complex_t` object. 
 */
complex_t transform(complex_t complex, form_t form) {
   // Check if the complex number is in appropriate form.
   assert ((complex.form == CARTESIAN || complex.form == POLAR) &&
           (form == CARTESIAN || form == POLAR));
   // Indicate the local variable/s.
   complex_t result;
   result.form = form;
   // Convert the one form to another form.
   if (complex.form == CARTESIAN)
      // Convert from the cartesian to the cartesian. 
      if (form == CARTESIAN)
         result.complex[0] = complex.complex[0], 
         result.complex[1] = complex.complex[1];
      // Convert from the cartesian to the polar.
      else
         result.complex[0] = sqrt(pow(complex.complex[0], 2) + 
                              pow(complex.complex[1], 2)), 
         result.complex[1] = DEG(atan(complex.complex[1] / 
                                  complex.complex[0])) + 180.0;
   else 
      // Convert from the polar to the cartesian.
      if (form == CARTESIAN)
         result.complex[0] = complex.complex[0] * 
                             cos(RAD(complex.complex[1])), 
         result.complex[1] = complex.complex[0] * 
                             sin(RAD(complex.complex[1]));
      // Convert from the polar to the polar.
      else
         result.complex[0] = complex.complex[0], 
         result.complex[1] = complex.complex[1];

   return result;
} 
 
/** @brief Add the 'complex1' and 'complex2' numbers.
 *  @param complex1 First complex number that will be added.
 *  @param complex2 Second complex number that will be added.
 *  @return `complex_t` object.
 */
complex_t add(complex_t complex1, complex_t complex2) {
   // Check if both complex numbers are is proper forms.
   assert ((complex1.form == CARTESIAN || complex1.form == POLAR) &&
           (complex2.form == CARTESIAN || complex2.form == POLAR));
   // Indicate the local variable/s.
   complex_t result;
   // It is easy to add complex numbers in cartesian form. So, 
   // convert the both complex numbers to cartesian form.
   complex1 = transform(complex1, CARTESIAN);
   complex2 = transform(complex2, CARTESIAN);
   // Add the complex numbers with each other.
   result.form = CARTESIAN;
   result.complex[0] = complex1.complex[0] + complex2.complex[0];
   result.complex[1] = complex1.complex[1] + complex2.complex[1];

   return result;
}

/** @brief Subtract the 'complex2' number from 'complex1' number.
 *  @param complex1 First complex number that will be subtracted.
 *  @param complex2 Second complex number that will be subtracted.
 *  @return `complex_t` object.
 */
complex_t subtract(complex_t complex1, complex_t complex2) {
   // Check if both complex numbers are is proper forms.
   assert ((complex1.form == CARTESIAN || complex1.form == POLAR) &&
           (complex2.form == CARTESIAN || complex2.form == POLAR));
   // Indicate the local variable/s.
   complex_t result;
   // It is easy to subtract complex numbers in cartesian form. So, 
   // convert the both complex numbers to cartesian form.
   complex1 = transform(complex1, CARTESIAN);
   complex2 = transform(complex2, CARTESIAN);
   // Subtract the complex numbers with each other.
   result.form = CARTESIAN;
   result.complex[0] = complex1.complex[0] - complex2.complex[0];
   result.complex[1] = complex1.complex[1] - complex2.complex[1];

   return result;
}

/** @brief Multiply the 'complex1' and 'complex2' numbers.
 *  @param complex1 First complex number that will be multiplied.
 *  @param complex2 Second complex number that will be multiplied.
 *  @return `complex_t` object.
 */
complex_t multiply(complex_t complex1, complex_t complex2) {
   // Check if both complex numbers are is proper forms.
   assert ((complex1.form == CARTESIAN || complex1.form == POLAR) &&
           (complex2.form == CARTESIAN || complex2.form == POLAR));
   // Indicate the local variable/s.
   complex_t result;
   // It is easy to subtract complex numbers in polar form. So, 
   // convert the both complex numbers to polar form.
   complex1 = transform(complex1, POLAR);
   complex2 = transform(complex2, POLAR);
   // Mltiply the complex numbers with each other.
   result.form = POLAR;
   result.complex[0] = complex1.complex[0] * complex2.complex[0];
   result.complex[1] = complex1.complex[1] + complex2.complex[1];

   return transform(result, CARTESIAN);
}

/** @brief Divide the 'complex2' number to 'complex1' number.
 *  @param complex1 First complex number that will be divided.
 *  @param complex2 Second complex number that will be divided.
 *  @return `complex_t` object.
 */
complex_t divide(complex_t complex1, complex_t complex2) {
   // Check if both complex numbers are is proper forms.
   assert ((complex1.form == CARTESIAN || complex1.form == POLAR) &&
           (complex2.form == CARTESIAN || complex2.form == POLAR));
   // Indicate the local variable/s.
   complex_t result;
   // It is easy to divide complex numbers in polar form. So, 
   // convert the both complex numbers to polar form.
   complex1 = transform(complex1, POLAR);
   complex2 = transform(complex2, POLAR);
   // Divide the complex numbers with each other.
   result.form = POLAR;
   result.complex[0] = complex1.complex[0] / complex2.complex[0];
   result.complex[1] = complex1.complex[1] - complex2.complex[1];

   return transform(result, CARTESIAN);
}

/** @brief Get the conjugate of the 'complex' number. 
 *  @param complex Complex number that will be conjugated.
 *  @return `complex_t` object.
 */
complex_t conjugate(complex_t complex) {
   // Check if the complex number is in proper form.
   assert (complex.form == CARTESIAN || complex.form == POLAR);
   // Indicate the local variable/s.
   complex_t result;
   // Get the conjugate of the complex number.
   result.form = CARTESIAN;
   result.complex[0] = transform(complex, CARTESIAN).complex[0];
   result.complex[1] = -1.0*transform(complex, CARTESIAN).complex[1];

   return result;
}

/** @brief Get the nth power of 'complex' number. 
 *  @param complex Complex number that will getted.
 *  @param n Nth power of the 'complex' number.
 *  @return `complex_t` object.
*/
complex_t power(complex_t complex, int n) {
   // Check if the complex number is in proper form.
   assert (complex.form == CARTESIAN || complex.form == POLAR);
   // Indicate the local variable/s.
   complex_t result;
   // Get the nth power of the complex number.
   result.form = POLAR;
   result.complex[0] = pow(transform(complex, POLAR).complex[0], n);
   result.complex[1] = transform(complex, POLAR).complex[1] * n;

   return transform(result, CARTESIAN);
}

/** @brief Get the nth root of 'complex' number. 
 *  @param complex Complex number that will getted.
 *  @param n Nth root of the 'complex' number.
 *  @return `complex_t` object.
*/
complex_t root(complex_t complex, int n) {
   // Check if the complex number is in proper form.
   assert (complex.form == CARTESIAN || complex.form == POLAR);
   // Indicate the local variable/s.
   complex_t result;
   // Get the nth root of the complex number.
   result.form = POLAR;
   result.complex[0] = pow(transform(complex, POLAR).complex[0], 
                           1.0 / n);
   result.complex[1] = transform(complex, POLAR).complex[1] / n;

   return transform(result, CARTESIAN);
}

/** @brief Return true, if both complex numbers are equal, 
 *         otherwise return false.
 *  @param complex1 First complex number that will be checked.
 *  @param complex2 Second complex number that will be checked.
 *  @return `boolean` object.
 */
boolean isequal(complex_t complex1, complex_t complex2) {
   // Transform the complex numbers in the same form.
   complex1 = transform(complex1, CARTESIAN);
   complex2 = transform(complex2, CARTESIAN);
   // Compare the component of the complex numbers.
   if ((complex1.complex[0] == complex2.complex[0]) && 
       (complex1.complex[1] == complex2.complex[1]))
      return true;
   else
      return false;
}

/** @brief Return true, if there is triangle inequality between 
 *         'complex1' and 'complex2' numbers, else return false.
 *  @param complex1 First complex number that will checked.
 *  @param complex2 Second complex number that will checked.
 *  @return `boolean` object.
 */
boolean istriangle(complex_t complex1, complex_t complex2) {
   // Transform the complex numbers in the same form.
   complex1 = transform(complex1, CARTESIAN);
   complex2 = transform(complex2, CARTESIAN);
   // Check the triangle inequality.
   if ((transform(complex1, POLAR).complex[1] + 
        transform(complex2, POLAR).complex[1]) >= 
       (transform(add(complex1, complex2), POLAR).complex[1]))
      return true;
   else 
      return false;
}
 