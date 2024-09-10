# ALAT (Advanced Linear Algebra Toolkit)

MAJOR := 2
MINOR := 0
PATCHLEVEL := 1

CC := gcc 
RM := rm -rf
AR := ar rcs
FLAGS := -c -fPIC -g

ALAT := libalat.a

MATRICES := ./source/matrices.c 
VECTORS := ./source/vectors.c 
APPS := ./source/apps.c 
COMPLEXES := ./source/complexes.c 
CRYPTS := ./source/crypts.c 
UTILS := ./source/utils.h 

OBJECTS := matrices.o vectors.o crypts.o apps.o complexes.o

$(ALAT): $(OBJECTS)
	$(AR) $(ALAT) $(OBJECTS)

matrices.o: $(MATRICES) $(UTILS)
	$(CC) $(MATRICES) $(FLAGS)

vectors.o: $(VECTORS) $(UTILS)
	$(CC) $(VECTORS) $(FLAGS)
 
crypts.o: $(CRYPTS) $(UTILS)
	$(CC) $(CRYPTS) $(FLAGS)

apps.o: $(APPS) $(UTILS)
	$(CC) $(APPS) $(FLAGS)

complexes.o: $(COMPLEXES) $(UTILS)
	$(CC) $(COMPLEXES) $(FLAGS)

clean:
	$(RM) $(OBJECTS)
