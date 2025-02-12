/* Different Coordinate Systems */

#include "../src/alat.h"

void main(int argc, char *argv[])
{
   int i;

   vector_t vector = {.dim = 3, .vector = {4, 7, -1}, .coor=cartesian};

   printf("x axis of 'vector':%f\n", alat_vector_car_x(vector));
   printf("y axis of 'vector':%f\n", alat_vector_car_y(vector));
   printf("z axis of 'vector':%f\n", alat_vector_car_z(vector));

   vector = alat_vector_transform(vector, cylindrical);

   printf("radial axis of 'vector':%f\n", alat_vector_cyl_radial(vector));
   printf("angular axis of 'vector (deg)':%f\n", alat_vector_cyl_angular(vector));
   printf("z axis of 'vector':%f\n", alat_vector_cyl_z(vector));  

   vector = alat_vector_transform(vector, spherical);

   printf("radial axis of 'vector':%f\n", alat_vector_sph_radial(vector));
   printf("polar axis of 'vector' (deg):%f\n", alat_vector_sph_polar(vector));
   printf("azimuthal axis of 'vector' (deg):%f\n", alat_vector_sph_azimuthal(vector));  

   exit(EXIT_SUCCESS);
}