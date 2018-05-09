# Graeme Gengras, May 2018
#
# Makefile for the 'querier' program
#   Builds, compiles and tests the program

# Compiler and flags
CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I ../common -L ../common -lcommon \
									  -I ../libcs50 -L ../libcs50 -lcs50

all: querier

querier: querier.c libcs50.a libcommon.a
	$(CC) -o $@ $< $(CFLAGS)

libcs50.a:
	cd ../libcs50; make

libcommon.a:
	cd ../common; make

.PHONY: test clean

test: querier
	./queriertest.sh

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f querier
	rm -f queriertest
