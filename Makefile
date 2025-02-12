# ALAT (Advanced Linear Algebra Toolkit)

MAJOR := 2
MINOR := 1
PATCHLEVEL := 0

CC := gcc 
CFLAGS := -g -lm 
AR := ar rcs 
RM := rm -rf 

SOURCES := src/*.c 
INCLUDES := src/*.h 
OBJECTS := matrices.o vectors.o complexes.o crypts.o apps.o
LIBRARY := libalat.a 
BINARY := alat

$(LIBRARY): $(OBJECTS)
	$(AR) $(LIBRARY) $(OBJECTS)
	$(CC) $(BINARY).c -o $(BINARY) -L. -lalat $(CFLAGS) 
	$(RM) $(OBJECTS)

$(OBJECTS): $(SOURCES) $(INCLUDES)
	$(CC) $(SOURCES) $(INCLUDES) -c $(CFLAGS)

.PHONY: clean 

clean:
	$(RM) $(LIBRARY) $(BINARY)
