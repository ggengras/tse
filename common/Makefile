# Graeme Gengras, April 2018
#
# Makefile for the 'common' library
#   Builds and compiles all functions into a library.

# object files, and the target library
OBJS = word.o pagedir.o index.o file.o glib.o
LIB = libcommon.a
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I ../libcs50
CC = gcc

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
word.o: word.h
pagedir.o: pagedir.h
index.o: index.h
file.o: file.h
glib.o: glib.h

.PHONY: clean

# clean up after our compilation
clean:
	rm -f $(LIB) *~ *.o *.a
