# Graeme Gengras, April 2018
#
# Makefile for the 'crawler' program
#   Builds, compiles and tests the program

# Compiler and flags
CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I ../libcs50 -L ../libcs50 -lcs50
PROG = crawler

.PHONY: test clean

all: $(PROG)

test: $(OBJS)
	make all
	./$(PROG) http://www.example.com output 2

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f $(PROG)
