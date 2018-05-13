# Graeme Gengras, April 2018
#
# Makefile for the 'crawler' program
#   Builds, compiles and tests the program

# Compiler and flags
CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I ../common -L ../common -lcommon \
									  -I ../libcs50 -L ../libcs50 -lcs50 -lcurl
PROG=crawler

all: $(PROG)

$(PROG): $(PROG).c libcs50.a libcommon.a
	$(CC) -o $@ $< $(CFLAGS)

libcs50.a:
	cd ../libcs50; make

libcommon.a:
	cd ../common; make

.PHONY: test clean

test: $(PROG)
	echo Running Integration Tests
	./testcrawler_int.sh

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f $(PROG)
	rm -rf crawler_test_output
