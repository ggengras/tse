# Graeme Gengras, April 2018
#
# Makefile for the 'indexer' program
#   Builds, compiles and tests the program

# Compiler and flags
CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I ../common -L ../common -lcommon \
									  -I ../libcs50 -L ../libcs50 -lcs50

all: indexer indextest

indexer: indexer.c libcs50.a libcommon.a
	$(CC) -o $@ $< $(CFLAGS)

indextest: indextest.c libcs50.a libcommon.a
	$(CC) -o $@ $< $(CFLAGS)

libcs50.a:
	cd ../libcs50; make

libcommon.a:
	cd ../common; make

.PHONY: test clean

test: indextext
	./indexertest.sh
	./indextest

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f indexer
	rm -f indextest
