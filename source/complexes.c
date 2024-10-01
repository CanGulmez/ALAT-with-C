/* Complex number operations in ALAT (Advanced Linear Algebra Toolkit) */

#include "./alat.h"

/**
 * Return true, if `complex` number is in cartesian form, 
 * otherwise return false.
 */
bool_t complexes_iscartesian(complex_t complex)
{
   return (!strcmp(complex.form, "cartesian")) ? true : false;
}

/**
 * Return true, if `complex` number is in polar form, 
 * otherwise return false.
 */
bool_t complexes_ispolar(complex_t complex)
{
   return (!strcmp(complex.form, "polar")) ? true : false;
}

/**
 * Return true if `complex` number is zero, otherwise return false.
 */
bool_t complexes_iszero(complex_t complex)
{
   return (complex.complex[0] == 0 && complex.complex[1] == 0) ? true : false;
} 

/**
 * Return true, if there is Triangular inequality, otherwise return false.
 */
bool_t complexes_istriangle(complex_t fcomplex, complex_t scomplex)
{
   complex_t fres, sres;

   fres = complexes_transform(fcomplex, "polar");
   sres = complexes_transform(scomplex, "polar");

   return (fres.complex[1] + sres.complex[1] >=
      complexes_add(fres, sres, "polar").complex[1]) ? true : false;
}
 
/**
 * Return true, if `fcomplex` and `scomplex` are equal, otherwise
 * return false.
 */
bool_t complexes_isequal(complex_t fcomplex, complex_t scomplex)
{
   if (strcmp(fcomplex.form, scomplex.form))
      return false;
 
   if (fcomplex.complex[0] != scomplex.complex[0] || 
       fcomplex.complex[1] != scomplex.complex[1])
      return false;

   return true;
}

/**
 * Retrun the zero complex number. `output_form` indicates
 * the output form of complex number and must be `cartesian`
 * or `polar`.
 */
complex_t complexes_zero(str_t output_form)
{
   complex_t result;

   result.form = output_form;
   result.complex[0] = 0.0, result.complex[1] = 0.0;

   return result;
}

/**
 * Transform `complex` number into particular `new_form`. Consistent forms that 
 * complex number can get are `cartesian` and `polar`. Note that in this module,
 * all angle will be represented as degrees (not radians). 
 */
complex_t complexes_transform(complex_t complex, str_t new_form)
{
   complex_t result;

   if (!strcmp(complex.form, "cartesian") && !strcmp(new_form, "cartesian")) {
      memcpy(&result, &complex, sizeof(complex));
   }
   else if (!strcmp(complex.form, "cartesian") && !strcmp(new_form, "polar")) {
      result.form = "polar";
      result.complex[0] = sqrt(pow(complex.complex[0], 2) + pow(complex.complex[1], 2));
      result.complex[1] = DEG(atan(complex.complex[1] / complex.complex[0])) + 180.0;
   }
   else if (!strcmp(complex.form, "polar") && !strcmp(new_form, "cartesian")) {
      result.form = "cartesian";
      result.complex[0] = complex.complex[0] * cos(RAD(complex.complex[1]));
      result.complex[1] = complex.complex[0] * sin(RAD(complex.complex[1]));
   }
   else if (!strcmp(complex.form, "polar") && !strcmp(new_form, "polar")) {
      memcpy(&result, &complex, sizeof(complex));
   }
   else
      alat_error("Complex number form must be 'cartesian' or 'polar'");
   
   return result;
}

/**
 * Return the real portion of `complex` number. If `complex` 
 * number defined in polar form, convert it to cartesian form. 
 */
double complexes_real(complex_t complex)
{
   if (!strcmp(complex.form, "cartesian"))
      return complex.complex[0];
   else
      return complexes_transform(complex, "cartesian").complex[0];
}

/**
 * Return the imaginary portion of `complex`.  If `complex` 
 * number defined in polar form, convert it to cartesian form. 
 */
double complexes_imaginary(complex_t complex)
{
   if (!strcmp(complex.form, "cartesian"))
      return complex.complex[1];
   else
      return complexes_transform(complex, "cartesian").complex[1];
}

/**
 * Return the modules portion of `complex`.  If `complex` 
 * number defined in cartesian form, convert it to polar form. 
 */
double complexes_modules(complex_t complex)
{
   if (!strcmp(complex.form, "polar"))
      return complex.complex[0];
   else
      return complexes_transform(complex, "polar").complex[0];  
}

/**
 * Return the argument portion of `complex`.  If `complex` 
 * number defined in cartesian form, convert it to polar form. 
 */
double complexes_argument(complex_t complex)
{
   if (!strcmp(complex.form, "polar"))
      return complex.complex[1];
   else
      return complexes_transform(complex, "polar").complex[1]; 
}

/**
 * Add up the `fcomplex` and `scomplex` numbers with each other. The result
 * complex number will be in form of `output_form` and must be `cartesian`, 
 * or `polar`.
 */
complex_t complexes_add(complex_t fcomplex, complex_t scomplex, str_t output_form)
{
   complex_t result;

   result = complexes_zero("cartesian");

   result.complex[0] = complexes_transform(fcomplex, "cartesian").complex[0] + 
      complexes_transform(scomplex, "cartesian").complex[0];
   result.complex[1] = complexes_transform(fcomplex, "cartesian").complex[1] + 
      complexes_transform(scomplex, "cartesian").complex[1];

   return complexes_transform(result, output_form);
}

/**
 * Subtract the `scomplex` number from `fcomplex` number. The result complex 
 * number will be in form of `output_form` and must be `cartesian` or `polar`.
 */
complex_t complexes_subtract(complex_t fcomplex, complex_t scomplex, str_t output_form)
{
   complex_t result;

   result = complexes_zero("cartesian");

   result.complex[0] = complexes_transform(fcomplex, "cartesian").complex[0] -
      complexes_transform(scomplex, "cartesian").complex[0];
   result.complex[1] = complexes_transform(fcomplex, "cartesian").complex[1] -
      complexes_transform(scomplex, "cartesian").complex[1];

   return complexes_transform(result, output_form);
}

/**
 * Multiply the `fcomplex` and `scomplex` with each other. The result complex 
 * number will be in form of `output_form` and must be `cartesian` or `polar`.
 */
complex_t complexes_multiply(complex_t fcomplex, complex_t scomplex, str_t output_form)
{
   complex_t result;

   result = complexes_zero("polar");

   result.complex[0] = complexes_transform(fcomplex, "polar").complex[0] *
      complexes_transform(scomplex, "polar").complex[0];
   result.complex[1] = complexes_transform(fcomplex, "polar").complex[1] +
      complexes_transform(scomplex, "polar").complex[1];

   return complexes_transform(result, output_form);
}

/**
 * Divide the `scomplex` to `fcomplex` with each other. The result complex 
 * number will be in form of `output_form` and must be `cartesian` or `polar`.
 */
complex_t complexes_divide(complex_t fcomplex, complex_t scomplex, str_t output_form)
{
   complex_t result;

   result = complexes_zero("polar");

   result.complex[0] = complexes_transform(fcomplex, "polar").complex[0] /
      complexes_transform(scomplex, "polar").complex[0];
   result.complex[1] = complexes_transform(fcomplex, "polar").complex[1] -
      complexes_transform(scomplex, "polar").complex[1];

   return complexes_transform(result, output_form);
}

/**
 * Get the `n`.th power of `complex` number. The result complex number 
 * will be in form of `output_form` and must be `cartesian` or `polar`.
 */
complex_t complexes_power(complex_t complex, double n, str_t output_form)
{
   complex_t result;

   result = complexes_zero("polar");

   result.complex[0] = pow(complexes_transform(complex, "polar").complex[0], n);
   result.complex[1] = complexes_transform(complex, "polar").complex[1] * n;

   return complexes_transform(result, output_form);  
}

/**
 * Get the `n`.th root of `complex` number. The result complex number 
 * will be in form of `output_form` and must be `cartesian` or `polar`.
 */
complex_t complexes_root(complex_t complex, double n, str_t output_form)
{
   complex_t result;

   result = complexes_zero("polar");

   result.complex[0] = pow(complexes_transform(complex, "polar").complex[0], 1/n);
   result.complex[1] = complexes_transform(complex, "polar").complex[1] / n;

   return complexes_transform(result, output_form);
}

/**
 * Get the conjugate of `complex` number. The result complex number 
 * will be in form of `output_form` and must be `cartesian` or `polar`.
 */
complex_t complexes_conjugate(complex_t complex, str_t output_form)
{
    complex_t result;

   result = complexes_zero("cartesian");

   result.complex[0] = complexes_transform(complex, "cartesian").complex[0];
   result.complex[1] = -1 * complexes_transform(complex, "cartesian").complex[1];

   return complexes_transform(result, output_form);
}

/**
 * Get the reciprocol of `complex` number. The result complex number 
 * will be in form of `output_form` and must be `cartesian` or `polar`.
 */
complex_t complexes_reciprocol(complex_t complex, str_t output_form)
{
   return complexes_power(complex, -1, output_form);
}
