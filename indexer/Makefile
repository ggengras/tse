# Graeme Gengras, April 2018
#
# Makefile for the 'indexer' program
#   Builds, compiles and tests the program

# Compiler and flags
CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I ../libcs50 -L ../libcs50 -lcs50 \
	-I ../common -L ../common -lcommon

all: indexer indexertest

indexer: indexer.c
	$(CC) -o $@ $< $(CFLAGS)

indexertest: indexertest.c
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: test clean

test: indexertext
	./indexertest.sh
	./indexertest

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f indexer
	rm -f indexertest
