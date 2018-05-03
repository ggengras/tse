# Graeme Gengras, April 2018
#
# Makefile for the 'indexer' program
#   Builds, compiles and tests the program

# Compiler and flags
CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I ../libcs50 -L ../libcs50 -lcs50 \
	-I ../common -L ../common -lcommon

all: indexer indextest

indexer: indexer.c
	$(CC) -o $@ $< $(CFLAGS)

indextest: indextest.c
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: test clean

test: indextext
	./indexertest.sh
	./indextest

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f indexer
	rm -f indextest
