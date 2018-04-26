# Graeme Gengras, April 2018
#
# Makefile for the 'crawler' program
#   Builds, compiles and tests the program

# Compiler and flags
CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I ../libcs50 -L ../libcs50 -lcs50
PROG=crawler

.PHONY: test clean newoutput

all: $(PROG)

test: $(OBJS)
	make all
	./$(PROG) http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ output 10

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f $(PROG)

newoutput:
	rm -rf output
	mkdir output
