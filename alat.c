/* ALAT (Advanced Linear Algebra Toolkit) CLI Program */

#include "./src/alat.h"

#define issame(fstring, sstring) (strcmp(fstring, sstring) == 0)

/**
 * Extract the boolean from `command`. 
 */
bool_t boolean(char * command)
{
   if (issame(command, "0") || issame(command, "false"))
      return false;
   if (issame(command, "1") || issame(command, "true"))
      return true;
}

/**
 * Extract the axis from `command`.
 */
axis_t axis(char * command)
{
   if (issame(command, "0") || issame(command, "hor")
       || issame(command, "horizontal"))
      return horizontal;
   if (issame(command, "1") || issame(command, "ver")
       || issame(command, "vertical"))
      return vertical;
}

/**
 * Extract the coordinate from `command`.
 */
coor_t coor(char * command)
{
   if (issame(command, "0") || issame(command, "car") 
       || issame(command, "cartesian"))
      return cartesian;
   if (issame(command, "1") || issame(command, "cyl") 
       || issame(command, "cylindrical"))
      return cylindrical;
   if (issame(command, "2") || issame(command, "sph") 
       || issame(command, "spherical"))
      return spherical;
}

/**
 * Extract the form from `command`. 
 */
form_t form(char * command)
{
   if (issame(command, "0") || issame(command, "dec")
       || issame(command, "decimal"))
      return decimal;
   if (issame(command, "1") || issame(command, "rad")
       || issame(command, "radians"))
      return radians;
   if (issame(command, "2") || issame(command, "deg")
       || issame(command, "degrees"))
      return degrees;
}

/**
 * Extract the format from `command`.
 */
format_t format(char * command)
{
   if (issame(command, "0") || issame(command, "alg") 
       || issame(command, "algebraic"))
      return algebraic;
   if (issame(command, "1") || issame(command, "pol")
       || issame(command, "polar"))
      return polar;
}

/**
 * Display the bool structure.
 */
void dbool(bool_t boolean)
{
   if (boolean == false)
      printf("false\n");
   if (boolean == true)
      printf("true\n");
}

/**
 * Display the coordinate.
 */
void dcoor(coor_t coor)
{
   if (coor == cartesian)
      printf("cartesian\n");
   if (coor == cylindrical)
      printf("cylindrical\n");
   if (coor == spherical)
      printf("spherical\n");
}

/**
 * Extract the shape structure from `command`.
 */
shape_t shape(char * command)
{
   shape_t result;

   result.row = atof(command);
   command = strchr(command, ',');
   command = strchr(command, command[1]);
   result.col = atof(command);

   return result;
}

/**
 * Extract the place structure from `command`.
 */
place_t place(char * command)
{
   place_t result;

   result.crow = atof(command);
   command = strchr(command, ',');
   command = strchr(command, command[1]);
   result.ccol = atof(command);

   return result;
}

/**
 * Extract the matrix structure from `command`.
 */
matrix_t matrix(char * command)
{
   int row, col, index, i, j;
   char string[strlen(command)];
   matrix_t result;

   row = 1; col = 1; index = 0;
   char delimeter[] = ",:";

   for (i = 0; i < strlen(command); i++)
      if (command[i] == ':')
         row ++;
   for (i = 0; command[i] != ':' && i < strlen(command); i++)
      if (command[i] == ',')
         col ++;
   
   result.shape.row = row; result.shape.col = col;
   double elements[row * col];
   strncpy(string, command, strlen(command));
   char *token = strtok(string, delimeter);

   while (token != NULL) {
      elements[index] = atof(token);
      index ++;
      token = strtok(NULL, delimeter);
   }
   index = 0;

   for (i = 0; i < result.shape.row; i++)
      for (j = 0; j < result.shape.col; j++)
         result.matrix[i][j] = elements[index], index++;

   return result;
}
 
/**
 * Eaxtract the vector structure from `command`.
 */
vector_t vector(char * command)
{
   int i;
   char *subcom;
   coor_t coor;
   vector_t result;

   result.dim = 0;
   while (true) {
      result.vector[result.dim] = atof(command);
      subcom = strchr(command, ',');
      if (subcom == NULL) {
         if (issame(command, "car") || 
             issame(command, "cartesian") ||
             issame(command, "0"))
            result.coor = cartesian;
         if (issame(command, "cyl") || 
             issame(command, "cylindrical") ||
             issame(command, "1"))
            result.coor = cylindrical;
         if (issame(command, "sph") || 
             issame(command, "spherical") ||
             issame(command, "2"))
            result.coor = spherical;
         break;
      }
      command = strchr(subcom, subcom[1]);
      result.dim ++;
   }
   return result;
}

/**
 * Extract the complex structure from `command`. 
 */
complex_t complex(char * command)
{
   complex_t result;

   result.complex[0] = atof(command);
   command = strchr(command, ',');
   command = strchr(command, command[1]);
   result.complex[1] = atof(command);
   command = strchr(command, ',');
   command = strchr(command, command[1]);
   if (issame(command, "alg") || 
       issame(command, "algebraic") ||
       issame(command, "0"))
      result.format = algebraic;
   if (issame(command, "pol") || 
       issame(command, "polar") ||
       issame(command, "1"))
      result.format = polar;

   return result;
}

/**
 * Extract the points structure from `command`.
 */
points_t points(char * command)
{
   int i;
   points_t result;

   i = 0;
   while (true) {
      result.points[i] = atof(command);
      command = strchr(command, ',');
      if (command == NULL)
         break;
      command = strchr(command, command[1]);
      i ++; 
   }
   result.length = i;

   return result;
}

/**
 * Display the shape structure.
 */
void dshape(shape_t shape)
{
   printf("%d,%d\n", shape.row, shape.col);
}

/**
 * Display the place structure. 
 */
void dplace(place_t place)
{
   printf("%d,%d\n", place.crow, place.ccol);
}

/**
 * Display the `matrix` structure.
 */
void dmatrix(matrix_t matrix)
{
   int i, j;

   for (i = 0; i < matrix.shape.row; i++) {
      for (j = 0; j < matrix.shape.col; j++) {
         printf("%.4f", matrix.matrix[i][j]);
         if (j + 1 != matrix.shape.col)
            printf(",");
      }
      if (i + 1 != matrix.shape.row)
         printf(":");
   }
   printf("\n");
}

/**
 * Display the `vector` structure.
 */
void dvector(vector_t vector)
{
   int i;

   for (i = 0; i < vector.dim; i++) 
      printf("%.4f,", vector.vector[i]);
   if (vector.coor == cartesian)
      printf("cartesian\n");
   if (vector.coor == cylindrical)
      printf("cylindrical\n");
   if (vector.coor == spherical)
      printf("spherical\n");
}

/**
 * Display the complex structure.
 */
void dcomplex(complex_t complex)
{
   printf("%.4f,%.4f,", complex.complex[0], 
      complex.complex[1]);
   if (complex.format == algebraic)
      printf("algebraic\n");
   if (complex.format == polar)
      printf("polar\n");
}
 
/**
 * Display the points structure.
 */
void dpoints(points_t points)
{
   int i;

   for (i = 0; i < points.length; i++) {
      printf("%.4f", points.points[i]);
      if (i + 1 != points.length)
         printf(",");
   }
   printf("\n");
}

/**
 * Display the usage error when typing wrong command/s.
 */
void usage_error(char * program)
{
   fprintf(stderr, "Usage: %s MODULE METHOD [PARAMS...]\n\n", program);
   fprintf(stderr, "\
ALAT (Advanced Linear Algebra Toolkit) is designed to automate for linear algebratic\n\
calculations. This toolkit offers five modules and related methods. These are 'matrices',\n\
'vectors', 'complexes', 'crypts', 'apps'. Matrices module implements matrix operation\n\
from basic matrix multiplication to advanced solving linear equation. It's the biggest\n\
module in the toolkit. Vectors module encompresses vector operation in which vectors can\n\
be defined in three different coordinate systems. Complexes module defines the complex\n\
number operations and its different defination types. Crypts module gives four different\n\
cryptography operations to encode/decode messages. Apps module includes real-world\n\
algebratic problems.\n\n\
NOTE: Please follow source code implementations to use from command-line.\n\n");
   fprintf(stderr, "General usage rules:\n");
   fprintf(stderr, "- Do not use any spaces when defining any kind of structure.\n");
   fprintf(stderr, "- Use comma and colon to define matrix such as '4,7:2,1' (2x2 matrix).\n");
   fprintf(stderr, "- Use comma to define matrix shapes such as '8,8' (8x8 shape)\n");
   fprintf(stderr, "- Use comma and informative coordinate system to define vector such 'as 4,1,2,car'\n\
  (3-dim vector in cartesian). You can use full coordinate name or first three\n\
  letters.\n");
   fprintf(stderr, "- Use comma and informative format to define complex number such as '4,7,alg'\n\
  (4 + 7i in algebraic format). You can use full format name or first three letters.\n");
   fprintf(stderr, "- Use comma to define points on a axis such as '1,4,5,7' (4 points on a axis).\n");
   fprintf(stderr, "- Use 'true' and 'false' for the boolean parameters.\n");
   fprintf(stderr, "- Use 'horizontal' and 'vertical' or first three letters to define axis.\n");
   fprintf(stderr, "- Use 'cartesian', 'cylindrical' and 'spherical' or first three letters to define\n\
  coordinate system.\n");
   fprintf(stderr, "- Use 'decimal', 'radians' and 'degrees' or first three letters to define angle.\n");
   fprintf(stderr, "- Use 'algebraic' and 'polar' or first three letters to define complex numbers.\n\n");
   fprintf(stderr, "Some examples:\n");
   fprintf(stderr, "- ./alat matrix det 4,7,1:2,4,5:-6,8,8           # determinant of 3x3 matrix\n");
   fprintf(stderr, "- ./alat matrix random 8,8                       # creating random 8x8 matrix\n");
   fprintf(stderr, "- ./alat vector angle 4,7,1,car 3,45,5,cyl deg   # angle between two vectors\n");
   fprintf(stderr, "- ./alat complex isequal 4,5,alg 7,120,pol       # checking complex equality\n");
   fprintf(stderr, "- ./alat crypt to_matrix 'Hello World...' 5,5    # convert message to 5x5 matrix\n");
   fprintf(stderr, "- ./alat app poly_curve_fitting 4,7,2 6,4,7      # polynomial curve fitting\n\n");
   fprintf(stderr, "About maintainer:\n");
   fprintf(stderr, "- Author: Ahmet Can GULMEZ\n");
   fprintf(stderr, "- E-Mail: ahmetcangulmez02@gmail.com\n");
   fprintf(stderr, "- Version: 2.1.0\n");
   fprintf(stderr, "- License: MIT License\n"); 
}

void main(int argc, char *argv[])
{
   char command[32];

   sprintf(command, "alat_%s_%s", argv[1], argv[2]);

   if (issame(command, "alat_matrix_issquare"))
      dbool(alat_matrix_issquare(matrix(argv[3])));
   else if (issame(command, "alat_matrix_ishomogen"))
      dbool(alat_matrix_ishomogen(matrix(argv[3])));
   else if (issame(command, "alat_matrix_iszeros"))
      dbool(alat_matrix_iszeros(matrix(argv[3])));
   else if (issame(command, "alat_matrix_isones"))
      dbool(alat_matrix_isones(matrix(argv[3])));
   else if (issame(command, "alat_matrix_isarbitrary"))
      dbool(alat_matrix_isarbitrary(matrix(argv[3]), atof(argv[4])));
   else if (issame(command, "alat_matrix_isidentity"))
      dbool(alat_matrix_isidentity(matrix(argv[3])));
   else if (issame(command, "alat_matrix_islowertri"))
      dbool(alat_matrix_islowertri(matrix(argv[3])));
   else if (issame(command, "alat_matrix_isuppertri"))
      dbool(alat_matrix_isuppertri(matrix(argv[3])));
   else if (issame(command, "alat_matrix_issymmetric"))
      dbool(alat_matrix_issymmetric(matrix(argv[3])));
   else if (issame(command, "alat_matrix_issame"))
      dbool(alat_matrix_isequal(matrix(argv[3]), matrix(argv[4])));
   else if (issame(command, "alat_matrix_istriangle"))
      dbool(alat_matrix_istriangle(matrix(argv[3])));
   else if (issame(command, "alat_matrix_isinvertible"))
      dbool(alat_matrix_isinvertible(matrix(argv[3])));
   else if (issame(command, "alat_matrix_shape"))
      dshape(alat_matrix_shape(matrix(argv[3])));
   else if (issame(command, "alat_matrix_zeros"))
      dmatrix(alat_matrix_zeros(shape(argv[3])));
   else if (issame(command, "alat_matrix_ones"))
      dmatrix(alat_matrix_ones(shape(argv[3])));
   else if (issame(command, "alat_matrix_identity"))
      dmatrix(alat_matrix_identity(shape(argv[3])));
   else if (issame(command, "alat_matrix_arbitrary"))
      dmatrix(alat_matrix_arbitrary(atof(argv[3]), shape(argv[4])));
   else if (issame(command, "alat_matrix_sequential"))
      dmatrix(alat_matrix_sequential(atof(argv[3]), atof(argv[4]), shape(argv[5])));
   else if (issame(command, "alat_matrix_random"))
      dmatrix(alat_matrix_random(shape(argv[3])));
   else if (issame(command, "alat_matrix_uniform"))
      dmatrix(alat_matrix_uniform(atoi(argv[3]), atoi(argv[4]), shape(argv[5])));
   else if (issame(command, "alat_matrix_randint"))
      dmatrix(alat_matrix_randint(atoi(argv[3]), atoi(argv[4]), shape(argv[5])));
   else if (issame(command, "alat_matrix_diagonal"))
      dmatrix(alat_matrix_diagonal(matrix(argv[3])));
   else if (issame(command, "alat_matrix_max"))
      printf("%.4f\n", alat_matrix_max(matrix(argv[3])));
   else if (issame(command, "alat_matrix_min"))
      printf("%.4f\n", alat_matrix_min(matrix(argv[3])));
   else if (issame(command, "alat_matrix_value"))
      printf("%.4f\n", alat_matrix_value(matrix(argv[3]), place(argv[4])));
   else if (issame(command, "alat_matrix_argmax"))
      dplace(alat_matrix_argmax(matrix(argv[3]), boolean(argv[4])));
   else if (issame(command, "alat_matrix_argmin"))
      dplace(alat_matrix_argmin(matrix(argv[3]), boolean(argv[4])));
   else if (issame(command, "alat_matrix_mean"))
      printf("%.4f\n", alat_matrix_mean(matrix(argv[3])));
   else if (issame(command, "alat_matrix_stddev"))
      printf("%.4f\n", alat_matrix_stddev(matrix(argv[3])));
   else if (issame(command, "alat_matrix_median"))
      printf("%.4f\n", alat_matrix_median(matrix(argv[3])));
   else if (issame(command, "alat_matrix_norm_one"))
      printf("%.4f\n", alat_matrix_norm_one(matrix(argv[3])));
   else if (issame(command, "alat_matrix_norm_infinity"))
      printf("%.4f\n", alat_matrix_norm_infinity(matrix(argv[3])));
   else if (issame(command, "alat_matrix_norm_frobenius"))
      printf("%.4f\n", alat_matrix_norm_frobenius(matrix(argv[3])));
   else if (issame(command, "alat_matrix_rank"))
      printf("%d\n", alat_matrix_rank(matrix(argv[3])));
   else if (issame(command, "alat_matrix_abs"))
      dmatrix(alat_matrix_abs(matrix(argv[3])));
   else if (issame(command, "alat_matrix_pow"))
      dmatrix(alat_matrix_pow(matrix(argv[3]), atof(argv[4])));
   else if (issame(command, "alat_matrix_sqrt"))
      dmatrix(alat_matrix_sqrt(matrix(argv[3])));
   else if (issame(command, "alat_matrix_root"))
      dmatrix(alat_matrix_root(matrix(argv[3]), atof(argv[4])));
   else if (issame(command, "alat_matrix_degrees"))
      dmatrix(alat_matrix_degrees(matrix(argv[3])));
   else if (issame(command, "alat_matrix_radians"))
      dmatrix(alat_matrix_radians(matrix(argv[3])));
   else if (issame(command, "alat_matrix_subset"))
      dmatrix(alat_matrix_subset(matrix(argv[3]), place(argv[4]), place(argv[5])));
   else if (issame(command, "alat_matrix_insert_row"))
      dmatrix(alat_matrix_insert_row(matrix(argv[3]), atof(argv[4]), atoi(argv[5])));
   else if (issame(command, "alat_matrix_insert_col"))
      dmatrix(alat_matrix_insert_col(matrix(argv[3]), atof(argv[4]), atoi(argv[5])));
   else if (issame(command, "alat_matrix_append_row"))
      dmatrix(alat_matrix_append_row(matrix(argv[3]), atof(argv[4])));
   else if (issame(command, "alat_matrix_append_col"))
      dmatrix(alat_matrix_append_col(matrix(argv[3]), atof(argv[4])));
   else if (issame(command, "alat_matrix_remove_row"))
      dmatrix(alat_matrix_remove_row(matrix(argv[3]), atoi(argv[4])));
   else if (issame(command, "alat_matrix_remove_col"))
      dmatrix(alat_matrix_remove_col(matrix(argv[3]), atoi(argv[4])));
   else if (issame(command, "alat_matrix_pop_row"))
      dmatrix(alat_matrix_pop_row(matrix(argv[3])));
   else if (issame(command, "alat_matrix_pop_col"))
      dmatrix(alat_matrix_pop_col(matrix(argv[3])));
   else if (issame(command, "alat_matrix_sort"))
      dmatrix(alat_matrix_sort(matrix(argv[3]), boolean(argv[4])));
   else if (issame(command, "alat_matrix_sum"))
      dmatrix(alat_matrix_sum(matrix(argv[3]), axis(argv[4])));
   else if (issame(command, "alat_matrix_pop_shuffle"))
      dmatrix(alat_matrix_shuffle(matrix(argv[3])));
   else if (issame(command, "alat_matrix_reshape"))
      dmatrix(alat_matrix_reshape(matrix(argv[3]), shape(argv[4])));
   else if (issame(command, "alat_matrix_transpose"))
      dmatrix(alat_matrix_transpose(matrix(argv[3])));
   else if (issame(command, "alat_matrix_concat"))
      dmatrix(alat_matrix_concat(matrix(argv[3]), matrix(argv[4]), axis(argv[5])));
   else if (issame(command, "alat_matrix_add"))
      dmatrix(alat_matrix_add(matrix(argv[3]), matrix(argv[4])));
   else if (issame(command, "alat_matrix_sub"))
      dmatrix(alat_matrix_sub(matrix(argv[3]), matrix(argv[4])));
   else if (issame(command, "alat_matrix_scalar_mul"))
      dmatrix(alat_matrix_scalar_mul(matrix(argv[3]), atof(argv[4])));
   else if (issame(command, "alat_matrix_dot_mul"))
      dmatrix(alat_matrix_dot_mul(matrix(argv[3]), matrix(argv[4])));
   else if (issame(command, "alat_matrix_cross_mul"))
      dmatrix(alat_matrix_cross_mul(matrix(argv[3]), matrix(argv[4])));
   else if (issame(command, "alat_matrix_scalar_div"))
      dmatrix(alat_matrix_scalar_div(matrix(argv[3]), atof(argv[4])));
   else if (issame(command, "alat_matrix_swap"))
      dmatrix(alat_matrix_swap(matrix(argv[3])));
   else if (issame(command, "alat_matrix_dot_mul"))
      dmatrix(alat_matrix_dot_mul(matrix(argv[3]), matrix(argv[4])));
   else if (issame(command, "alat_matrix_det"))
      printf("%.4f\n", alat_matrix_det(matrix(argv[3])));
   else if (issame(command, "alat_matrix_minors"))
      dmatrix(alat_matrix_minors(matrix(argv[3])));
   else if (issame(command, "alat_matrix_cofactor"))
      dmatrix(alat_matrix_cofactors(matrix(argv[3])));
   else if (issame(command, "alat_matrix_adjoint"))
      dmatrix(alat_matrix_adjoint(matrix(argv[3])));
   else if (issame(command, "alat_matrix_inverse"))
      dmatrix(alat_matrix_inverse(matrix(argv[3])));
   else if (issame(command, "alat_matrix_uppertri"))
      dmatrix(alat_matrix_uppertri(matrix(argv[3])));
   else if (issame(command, "alat_matrix_lowertri"))
      dmatrix(alat_matrix_lowertri(matrix(argv[3])));
   else if (issame(command, "alat_matrix_solve"))
      dmatrix(alat_matrix_solve(matrix(argv[3])));

   else if (issame(command, "alat_vector_transform"))
      dvector(alat_vector_transform(vector(argv[3]), coor(argv[4])));
   else if (issame(command, "alat_vector_iscartesian"))
      dbool(alat_vector_iscartesian(vector(argv[3])));
   else if (issame(command, "alat_vector_iscylindrical"))
      dbool(alat_vector_iscylindrical(vector(argv[3])));
   else if (issame(command, "alat_vector_isspherical"))
      dbool(alat_vector_isspherical(vector(argv[3])));
   else if (issame(command, "alat_vector_iszeros"))
      dbool(alat_vector_iszeros(vector(argv[3])));
   else if (issame(command, "alat_vector_isones"))
      dbool(alat_vector_isones(vector(argv[3])));
   else if (issame(command, "alat_vector_isequal"))
      dbool(alat_vector_isequal(vector(argv[3]), vector(argv[4])));
   else if (issame(command, "alat_vector_isarbitrary"))
      dbool(alat_vector_isarbitrary(vector(argv[3]), atof(argv[4])));
   else if (issame(command, "alat_vector_iscasc"))
      dbool(alat_vector_iscasc(vector(argv[3]), vector(argv[4])));
   else if (issame(command, "alat_vector_istriangle"))
      dbool(alat_vector_istriangle(vector(argv[3]), vector(argv[4])));
   else if (issame(command, "alat_vector_ispythagorean"))
      dbool(alat_vector_ispythagorean(vector(argv[3]), vector(argv[4])));
   else if (issame(command, "alat_vector_issteep"))
      dbool(alat_vector_issteep(vector(argv[3]), vector(argv[4])));
   else if (issame(command, "alat_vector_isparallel"))
      dbool(alat_vector_isparallel(vector(argv[3]), vector(argv[4])));
   else if (issame(command, "alat_vector_car_n"))
      printf("%.4f\n", alat_vector_car_n(vector(argv[3]), atoi(argv[4])));
   else if (issame(command, "alat_vector_car_x"))
      printf("%.4f\n", alat_vector_car_x(vector(argv[3])));
   else if (issame(command, "alat_vector_car_y"))
      printf("%.4f\n", alat_vector_car_y(vector(argv[3])));
   else if (issame(command, "alat_vector_car_z"))
      printf("%.4f\n", alat_vector_car_z(vector(argv[3])));
   else if (issame(command, "alat_vector_cyl_radial"))
      printf("%.4f\n", alat_vector_cyl_radial(vector(argv[3])));
   else if (issame(command, "alat_vector_cyl_polar"))
      printf("%.4f\n", alat_vector_cyl_angular(vector(argv[3])));
   else if (issame(command, "alat_vector_cyl_z"))
      printf("%.4f\n", alat_vector_cyl_z(vector(argv[3])));
   else if (issame(command, "alat_vector_sph_radial"))
      printf("%.4f\n", alat_vector_sph_radial(vector(argv[3])));
   else if (issame(command, "alat_vector_sph_polar"))
      printf("%.4f\n", alat_vector_sph_polar(vector(argv[3])));
   else if (issame(command, "alat_vector_sph_azimuthal"))
      printf("%.4f\n", alat_vector_sph_azimuthal(vector(argv[3])));
   else if (issame(command, "alat_vector_zeros"))
      dvector(alat_vector_zeros(atoi(argv[3]), coor(argv[4])));
   else if (issame(command, "alat_vector_ones"))
      dvector(alat_vector_ones(atoi(argv[3]), coor(argv[4])));
   else if (issame(command, "alat_vector_arbitrary"))
      dvector(alat_vector_arbitrary(atof(argv[3]), atoi(argv[4]), coor(argv[5])));
   else if (issame(command, "alat_vector_sequential"))
      dvector(alat_vector_sequential(atof(argv[3]), atof(argv[4]), atoi(argv[5]), coor(argv[6])));
   else if (issame(command, "alat_vector_random"))
      dvector(alat_vector_random(atoi(argv[3]), coor(argv[4])));
   else if (issame(command, "alat_vector_uniform"))
      dvector(alat_vector_uniform(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), coor(argv[6])));
   else if (issame(command, "alat_vector_randint"))
      dvector(alat_vector_randint(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), coor(argv[6])));
   else if (issame(command, "alat_vector_dim"))
      printf("%d\n", alat_vector_dim(vector(argv[3])));
   else if (issame(command, "alat_vector_coor"))
      dcoor(alat_vector_coor(vector(argv[3])));
   else if (issame(command, "alat_vector_lenght"))
      printf("%.4f\n", alat_vector_lenght(vector(argv[3])));
   else if (issame(command, "alat_vector_magnitude"))
      printf("%.4f\n", alat_vector_magnitude(vector(argv[3])));
   else if (issame(command, "alat_vector_abs"))
      dvector(alat_vector_abs(vector(argv[3]), coor(argv[4])));
   else if (issame(command, "alat_vector_pow"))
      dvector(alat_vector_pow(vector(argv[3]), atof(argv[4]), coor(argv[5])));
   else if (issame(command, "alat_vector_root"))
      dvector(alat_vector_root(vector(argv[3]), atof(argv[4]), coor(argv[5])));
   else if (issame(command, "alat_vector_sqrt"))
      dvector(alat_vector_sqrt(vector(argv[3]), coor(argv[4])));
   else if (issame(command, "alat_vector_unit"))
      dvector(alat_vector_unit(vector(argv[3]), coor(argv[4])));
   else if (issame(command, "alat_vector_add"))
      dvector(alat_vector_add(vector(argv[3]), vector(argv[4]), coor(argv[5])));
   else if (issame(command, "alat_vector_sub"))
      dvector(alat_vector_sub(vector(argv[3]), vector(argv[4]), coor(argv[5])));
   else if (issame(command, "alat_vector_scalar_mul"))
      dvector(alat_vector_scalar_mul(vector(argv[3]), atof(argv[4]), coor(argv[5])));
   else if (issame(command, "alat_vector_distance"))
      printf("%.4f\n", alat_vector_distance(vector(argv[3]), vector(argv[4])));
   else if (issame(command, "alat_vector_dot_mul"))
      printf("%.4f\n", alat_vector_dot_mul(vector(argv[3]), vector(argv[4])));
   else if (issame(command, "alat_vector_cross_mul"))
      dvector(alat_vector_cross_mul(vector(argv[3]), vector(argv[4]), coor(argv[5])));
   else if (issame(command, "alat_vector_project"))
      dvector(alat_vector_project(vector(argv[3]), vector(argv[4]), coor(argv[5])));
   else if (issame(command, "alat_vector_reflect"))
      dvector(alat_vector_reflect(vector(argv[3]), vector(argv[4]), coor(argv[5])));
   else if (issame(command, "alat_vector_interpolate"))
      dvector(alat_vector_interpolate(vector(argv[3]), vector(argv[4]), atof(argv[5]), coor(argv[6])));
   else if (issame(command, "alat_vector_angle"))
      printf("%.4f\n", alat_vector_angle(vector(argv[3]), vector(argv[4]), form(argv[5])));

   else if (issame(command, "alat_complex_transform"))
      dcomplex(alat_complex_transform(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_isalgebraic"))
      dbool(alat_complex_isalgebraic(complex(argv[3])));
   else if (issame(command, "alat_complex_ispolar"))
      dbool(alat_complex_ispolar(complex(argv[3])));
   else if (issame(command, "alat_complex_iszero"))
      dbool(alat_complex_iszero(complex(argv[3])));
   else if (issame(command, "alat_complex_istriangle"))
      dbool(alat_complex_istriangle(complex(argv[3]), complex(argv[4])));
   else if (issame(command, "alat_complex_isequal"))
      dbool(alat_complex_isequal(complex(argv[3]), complex(argv[4])));
   else if (issame(command, "alat_complex_zero"))
      dcomplex(alat_complex_zero(format(argv[3])));
   else if (issame(command, "alat_complex_real"))
      printf("%.4f\n", alat_complex_real(complex(argv[3])));
   else if (issame(command, "alat_complex_imaginary"))
      printf("%.4f\n", alat_complex_imaginary(complex(argv[3])));
   else if (issame(command, "alat_complex_magnitude"))
      printf("%.4f\n", alat_complex_magnitude(complex(argv[3])));
   else if (issame(command, "alat_complex_argument"))
      printf("%.4f\n", alat_complex_argument(complex(argv[3])));
   else if (issame(command, "alat_complex_sin"))
      dcomplex(alat_complex_sin(complex(argv[3]), format(argv[4])));

   else if (issame(command, "alat_complex_cos"))
      dcomplex(alat_complex_cos(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_tan"))
      dcomplex(alat_complex_tan(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_sinh"))
      dcomplex(alat_complex_sinh(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_cosh"))
      dcomplex(alat_complex_cosh(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_tanh"))
      dcomplex(alat_complex_tanh(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_asin"))
      dcomplex(alat_complex_asin(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_acos"))
      dcomplex(alat_complex_acos(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_asinh"))
      dcomplex(alat_complex_asinh(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_acosh"))
      dcomplex(alat_complex_acosh(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_log"))
      dcomplex(alat_complex_log(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_log2"))
      dcomplex(alat_complex_log2(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_log10"))
      dcomplex(alat_complex_log10(complex(argv[3]), format(argv[4])));
   else if (issame(command, "alat_complex_logx"))
      dcomplex(alat_complex_logx(complex(argv[3]), atof(argv[4]), format(argv[5])));
   else if (issame(command, "alat_complex_add"))
      dcomplex(alat_complex_add(complex(argv[3]), complex(argv[4]), format(argv[5])));
   else if (issame(command, "alat_complex_scalar_mul"))
      dcomplex(alat_complex_scalar_mul(complex(argv[3]), atof(argv[4]), format(argv[5])));
   else if (issame(command, "alat_complex_scalar_div"))
      dcomplex(alat_complex_scalar_div(complex(argv[3]), atof(argv[4]), format(argv[5])));
   else if (issame(command, "alat_complex_sub"))
      dcomplex(alat_complex_sub(complex(argv[3]), complex(argv[4]), format(argv[5])));
   else if (issame(command, "alat_complex_mul"))
      dcomplex(alat_complex_mul(complex(argv[3]), complex(argv[4]), format(argv[5])));
   else if (issame(command, "alat_complex_div"))
      dcomplex(alat_complex_div(complex(argv[3]), complex(argv[4]), format(argv[5])));
   else if (issame(command, "alat_complex_pow"))
      dcomplex(alat_complex_pow(complex(argv[3]), atof(argv[4]), format(argv[5])));
   else if (issame(command, "alat_complex_root"))
      dcomplex(alat_complex_root(complex(argv[3]), atof(argv[4]), format(argv[5])));
   else if (issame(command, "alat_complex_sqrt"))
      dcomplex(alat_complex_sqrt(complex(argv[3]), format(argv[5])));
   else if (issame(command, "alat_complex_conjugate"))
      dcomplex(alat_complex_conjugate(complex(argv[3]), format(argv[5])));
   else if (issame(command, "alat_complex_reciprocol"))
      dcomplex(alat_complex_reciprocol(complex(argv[3]), format(argv[5])));

   else if (issame(command, "alat_crypt_to_matrix"))
      dmatrix(alat_crypt_to_matrix(argv[3], shape(argv[4])));
   else if (issame(command, "alat_crypt_encode"))
      dmatrix(alat_crypt_encode(argv[3], matrix(argv[4])));
   else if (issame(command, "alat_crypt_decode"))
      dmatrix(alat_crypt_decode(matrix(argv[3]), matrix(argv[4])));
   else if (issame(command, "alat_crypt_to_message"))
      printf("%s\n", alat_crypt_to_message(matrix(argv[3]), matrix(argv[4])));

   else if (issame(command, "alat_app_poly_curve_fitting"))
      dpoints(alat_app_poly_curve_fitting(points(argv[3]), points(argv[4])));
   else if (issame(command, "alat_app_least_squares_reg"))
      dpoints(alat_app_least_sqaures_reg(points(argv[3]), points(argv[4])));
   else if (issame(command, "alat_app_area"))
      printf("%.4f\n", alat_app_area(points(argv[3]), points(argv[4])));
   else if (issame(command, "alat_app_volume"))
      printf("%.4f\n", alat_app_volume(points(argv[3]), points(argv[4]), points(argv[5])));

   else usage_error(argv[0]);

   exit(EXIT_SUCCESS);
}
