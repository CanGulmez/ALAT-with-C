/* Complex number operations in ALAT (Advanced Linear Algebra Toolkit) */

#include "./alat.h"

/**
 * Transform `complex` number into new `format`. `format` must be `algebraic` or 
 * `polar`. Note that arguments of complex numbers will be represented as degrees. 
 */
complex_t alat_complex_transform(complex_t complex, format_t format)
{
   complex_t result;

   assert_complex(complex);
   assert (format == algebraic || format == polar); 
   result.format = format;

   if ((complex.format == algebraic && format == algebraic) || 
       (complex.format == polar && format == polar)) 
      result.complex[0] = complex.complex[0], result.complex[1] = complex.complex[1];
   else if (complex.format == algebraic && format == polar) 
      result.complex[0] = sqrt(pow(complex.complex[0], 2) + pow(complex.complex[1], 2)),
      result.complex[1] = DEG(atan(complex.complex[1] / complex.complex[0]));
   else if (complex.format == polar && format == algebraic) 
      result.complex[0] = complex.complex[0] * cos(RAD(complex.complex[1])),
      result.complex[1] = complex.complex[0] * sin(RAD(complex.complex[1]));
   
   return result;
}

/**
 * Return `true`, if `complex` number is in algebraic 
 * format, otherwise return `false`.
 */
bool_t alat_complex_isalgebraic(complex_t complex)
{
   return (complex.format == algebraic) ? true : false;
}

/**
 * Return `true`, if `complex` number is in polar 
 * format, otherwise return `false`.
 */
bool_t alat_complex_ispolar(complex_t complex)
{
   return (complex.format == polar) ? true : false;
}
 
/**
 * Return `true` if `complex` number is zero, otherwise return `false`.
 */
bool_t alat_complex_iszero(complex_t complex)
{
   return (complex.complex[0] == 0 && complex.complex[1] == 0) ? true : false;
} 

/**
 * Return `true`, if there is Triangular inequality, otherwise return `false`.
 */
bool_t alat_complex_istriangle(complex_t fcomplex, complex_t scomplex)
{
   fcomplex = alat_complex_transform(fcomplex, polar);
   scomplex = alat_complex_transform(scomplex, polar);

   return (fcomplex.complex[1] + scomplex.complex[1] >=
      alat_complex_add(fcomplex, scomplex, polar).complex[1]) ? true : false;
}
 
/**
 * Return `true`, if `fcomplex` and `scomplex` are equal, otherwise
 * return `false`.
 */
bool_t alat_complex_isequal(complex_t fcomplex, complex_t scomplex)
{
   fcomplex = alat_complex_transform(fcomplex, algebraic);
   scomplex = alat_complex_transform(scomplex, algebraic);
 
   if (fcomplex.complex[0] != scomplex.complex[0] || 
       fcomplex.complex[1] != scomplex.complex[1])
      return false;

   return true;
}

/**
 * Create zero complex number which will has `format`.
 */
complex_t alat_complex_zero(format_t format)
{
   complex_t result;

   assert (format == algebraic || format == polar);

   result.format = format;
   result.complex[0] = 0.0; result.complex[1] = 0.0;

   return result;
}

/**
 * Return the real part of `complex` number.
 */
double alat_complex_real(complex_t complex)
{
   return alat_complex_transform(complex, algebraic).complex[0];
}

/**
 * Return the imaginary part of `complex` number.
 */
double alat_complex_imaginary(complex_t complex)
{
   return alat_complex_transform(complex, algebraic).complex[1];
}

/**
 * Return the magnitude part of `complex` number.
 */
double alat_complex_magnitude(complex_t complex)
{
   return alat_complex_transform(complex, polar).complex[0];
}

/**
 * Return the argument (deg) part of `complex` number.
 */
double alat_complex_argument(complex_t complex)
{
   return alat_complex_transform(complex, polar).complex[1];
}

/**
 * Return sine of `complex` number which will be defined in `format`.
 */
complex_t alat_complex_sin(complex_t complex, format_t format)
{
   complex_t result;

   complex = alat_complex_transform(complex, algebraic);
   result.format = algebraic;
   result.complex[0] = sin(complex.complex[0]) * cosh(complex.complex[1]);
   result.complex[1] = cos(complex.complex[0]) * sinh(complex.complex[1]);

   return alat_complex_transform(result, format);
}

/**
 * Return cosine of `complex` number which will be defined in `format`.
 */
complex_t alat_complex_cos(complex_t complex, format_t format)
{
   complex_t result;

   complex = alat_complex_transform(complex, algebraic);
   result.format = algebraic;
   result.complex[0] = cos(complex.complex[0]) * cosh(complex.complex[1]);
   result.complex[1] = -1 * sin(complex.complex[0]) * sinh(complex.complex[1]);

   return alat_complex_transform(result, format);
}

/**
 * Return tangent of `complex` number which will be defined 
 * in `format`.
 */
complex_t alat_complex_tan(complex_t complex, format_t format)
{
   complex_t result;

   result = alat_complex_div(alat_complex_sin(complex, algebraic), 
      alat_complex_cos(complex, algebraic), algebraic);

   return alat_complex_transform(result, format);
}

/**
 * Return hyperbolic sine of `complex` number which will be 
 * defined in `format`.
 */
complex_t alat_complex_sinh(complex_t complex, format_t format)
{
   complex_t result;

   complex = alat_complex_transform(complex, algebraic);
   result.format = algebraic;
   result.complex[0] = sinh(complex.complex[0]) * cos(complex.complex[1]);
   result.complex[1] = cosh(complex.complex[0]) * sin(complex.complex[1]);

   return alat_complex_transform(result, format);
}

/**
 * Return hyperbolic cosine of `complex` number which will be 
 * defined in `format`.
 */
complex_t alat_complex_cosh(complex_t complex, format_t format)
{
   complex_t result;

   complex = alat_complex_transform(complex, algebraic);
   result.format = algebraic;
   result.complex[0] = cosh(complex.complex[0]) * cos(complex.complex[1]);
   result.complex[1] = sinh(complex.complex[0]) * sin(complex.complex[1]);

   return alat_complex_transform(result, format);
}

/**
 * Return hyperbolic tangent of `complex` number which will be 
 * defined in `format`.
 */
complex_t alat_complex_tanh(complex_t complex, format_t format)
{
   return alat_complex_transform(alat_complex_div(
      alat_complex_sinh(complex, algebraic), 
      alat_complex_cosh(complex, algebraic), algebraic), format);
}

/**
 * Return the arc sine of `complex` number which will be defined 
 * in `format`.
 */
complex_t alat_complex_asin(complex_t complex, format_t format)
{
   complex_t inter, last, result;

   complex = alat_complex_transform(complex, algebraic);
   inter.format = algebraic;
   last.format = algebraic;
   result.format = algebraic;
   inter.complex[0] = 1.0 - pow(complex.complex[0], 2.0) + 
      pow(complex.complex[1], 2.0);
   inter.complex[1] = -2.0 * complex.complex[1] * 
      complex.complex[0];
   inter = alat_complex_sqrt(inter, algebraic);
   last.complex[0] = inter.complex[0] - complex.complex[1];
   last.complex[1] = complex.complex[0] + inter.complex[1];
   last = alat_complex_log(last, algebraic);
   result.complex[0] = last.complex[1];
   result.complex[1] = -1.0 * last.complex[0];

   return alat_complex_transform(result, format);
}

/**
 * Return the arc cosine of `complex` number which will be 
 * defined in `format`.
 */
complex_t alat_complex_acos(complex_t complex, format_t format)
{
   complex_t result;

   complex = alat_complex_asin(complex, algebraic);
   result.format = algebraic;
   result.complex[0] = RAD(180.0 / 2.0) - complex.complex[0];
   result.complex[1] = -1.0 * complex.complex[1];

   return alat_complex_transform(result, format);
}

/**
 * Return the arc hyperbolic sine of `complex` number which 
 * will be defined in `format`.
 */
complex_t alat_complex_asinh(complex_t complex, format_t format)
{
   complex_t result;

   complex = alat_complex_transform(complex, algebraic);
   result = alat_complex_pow(complex, 2.0, algebraic);
   result.complex[0] ++;
   result = alat_complex_sqrt(result, algebraic);
   result = alat_complex_add(complex, result, algebraic);
   result = alat_complex_log(result, algebraic);

   return alat_complex_transform(result, format);
}

complex_t alat_complex_acosh(complex_t complex, format_t format)
{
   complex_t result;

   result.format = algebraic;
   complex = alat_complex_transform(complex, algebraic);
   complex = alat_complex_pow(complex, 2.0, algebraic);
   complex.complex[0] --;
   complex = alat_complex_sqrt(complex, algebraic);
   complex = alat_complex_asinh(complex, algebraic);
   result.complex[0] = -1.0 * complex.complex[1];
   result.complex[1] = complex.complex[0];

   return result;
}
 
/**
 * Return the natural logarithm of `complex` number which will 
 * be defined in `format`.
 */
complex_t alat_complex_log(complex_t complex, format_t format)
{
   complex_t result;

   result.format = algebraic;
   complex = alat_complex_transform(complex, algebraic);
   result.complex[0] = log(alat_complex_magnitude(complex));
   result.complex[1] = RAD(alat_complex_argument(complex));

   return alat_complex_transform(result, format);
}

/**
 * Return the `x` based logarithm of `complex` number which will be defined 
 * in `format`.
 */
complex_t alat_complex_logx(complex_t complex, double x, format_t format)
{
   return alat_complex_transform(alat_complex_scalar_div(
      alat_complex_log(complex, algebraic), log(x), algebraic), format);
}

/**
 * Return the 2-based logarithm of `complex` number which will 
 * be defined in `format`.
 */
complex_t alat_complex_log2(complex_t complex, format_t format)
{
   return alat_complex_logx(complex, 2.0, format);
}

/**
 * Return the 10-based logarithm of `complex` number which will 
 * be defined in `format`.
 */
complex_t alat_complex_log10(complex_t complex, format_t format)
{
   return alat_complex_logx(complex, 10.0, format);
}

/**
 * Add the `fcomplex` and `complex` with each other which will be defined in `format`.
 */
complex_t alat_complex_add(complex_t fcomplex, complex_t scomplex, format_t format)
{
   complex_t result;

   result.format = algebraic;
   result.complex[0] = alat_complex_transform(fcomplex, algebraic).complex[0] + 
      alat_complex_transform(scomplex, algebraic).complex[0];
   result.complex[1] = alat_complex_transform(fcomplex, algebraic).complex[1] + 
      alat_complex_transform(scomplex, algebraic).complex[1];

   return alat_complex_transform(result, format);
}

/**
 * Multiply the `complex` by `scalar` which will be defined in `format`.
 */
complex_t alat_complex_scalar_mul(complex_t complex, double scalar, format_t format)
{
   complex_t result;

   result.format = algebraic;
   result.complex[0] = alat_complex_transform(complex, cartesian).complex[0] * scalar; 
   result.complex[1] = alat_complex_transform(complex, cartesian).complex[1] * scalar; 

   return alat_complex_transform(result, format);
}

/**
 * Divide the `complex` number by `scalar` which wiil be defined in `format`.
 */
complex_t alat_complex_scalar_div(complex_t complex, double scalar, format_t format)
{
   return alat_complex_scalar_mul(complex, 1 / scalar, format);
}

/**
 * Subtract the `scomplex` from `fcomplex` and then convert it to `format`.
 */
complex_t alat_complex_sub(complex_t fcomplex, complex_t scomplex, format_t format)
{
   return alat_complex_add(fcomplex, alat_complex_scalar_mul(scomplex, -1.0, algebraic), format);
}

/**
 * Multiply the `fcomplex` and `scomplex` with each other and convert it to `format`.
 */
complex_t alat_complex_mul(complex_t fcomplex, complex_t scomplex, format_t format)
{
   complex_t result;

   result.format = polar;
   result.complex[0] = alat_complex_transform(fcomplex, polar).complex[0] *
      alat_complex_transform(scomplex, polar).complex[0];
   result.complex[1] = alat_complex_transform(fcomplex, polar).complex[1] +
      alat_complex_transform(scomplex, polar).complex[1];

   return alat_complex_transform(result, format);
}

/**
 * Divide the `fcomplex` to `scomplex` with each other and convert it to `format`.
 */
complex_t alat_complex_div(complex_t fcomplex, complex_t scomplex, format_t format)
{
   complex_t result;

   result.format = polar;
   result.complex[0] = alat_complex_transform(fcomplex, polar).complex[0] /
      alat_complex_transform(scomplex, polar).complex[0];
   result.complex[1] = alat_complex_transform(fcomplex, polar).complex[1] -
      alat_complex_transform(scomplex, polar).complex[1];

   return alat_complex_transform(result, format);
}

/**
 * Get the `n`.th pow of `complex` number and then covert it to `format`.
 */
complex_t alat_complex_pow(complex_t complex, double n, format_t format)
{
   complex_t result;

   result.format = polar;
   result.complex[0] = pow(alat_complex_transform(complex, polar).complex[0], n);
   result.complex[1] = alat_complex_transform(complex, polar).complex[1] * n;

   return alat_complex_transform(result, format);  
}

/**
 * Get the `n`.th root of `complex` number and then convert it to `format`.
 */
complex_t alat_complex_root(complex_t complex, double n, format_t format)
{
   complex_t result;

   result.format = polar;
   result.complex[0] = pow(alat_complex_transform(complex, polar).complex[0], 1/n);
   result.complex[1] = alat_complex_transform(complex, polar).complex[1] / n;

   return alat_complex_transform(result, format);
}

/**
 * Get the square root of `complex` number and convert to `format`.
 */
complex_t alat_complex_sqrt(complex_t complex, format_t format)
{
   return alat_complex_root(complex, 2.0, format);
}
 
/**
 * Get the conjugate of `complex` number and then convert to `format`.
 */
complex_t alat_complex_conjugate(complex_t complex, format_t format)
{
    complex_t result;

   result.format = cartesian;
   result.complex[0] = alat_complex_transform(complex, cartesian).complex[0];
   result.complex[1] = -1 * alat_complex_transform(complex, cartesian).complex[1];

   return alat_complex_transform(result, format);
}

/**
 * Get the reciprocol of `complex` number and convert it to `format`.
 */
complex_t alat_complex_reciprocol(complex_t complex, format_t format)
{
   return alat_complex_pow(complex, -1.0, format);
}
