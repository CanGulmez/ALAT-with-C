# An example Makefile scripts for ALAT vector applications.

# Object files to compile program.
objects = vectors.o vector_properties.o

# The main script to compile program.
main : $(objects)
	gcc $(objects) -o main -lm

# Object file definations.
vectors.o 			  : ./include/vectors.h
vector_properties.o : ./include/vectors.h
# $(objects)			  : ./include/vectors.h

.PHONY : clean

clean :
	rm main $(objects)
