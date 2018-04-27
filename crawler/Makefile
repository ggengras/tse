# Graeme Gengras, April 2018
#
# Makefile for the 'crawler' program
#   Builds, compiles and tests the program

# Compiler and flags
CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I ../libcs50 -L ../libcs50 -lcs50
PROG=crawler

all: $(PROG)

$(PROG): $(PROG).c
	$(CC) -o $@ $< $(CFLAGS)

testcrawler_unit: testcrawler_unit.c crawler.c

.PHONY: test clean newoutput

test: $(PROG) testcrawler_unit.c
	echo *** Running Unit Tests ***
	./testcrawler_unit
	echo *** Running Integration Tests ***
	./testcrawler_int.sh

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f $(PROG)
	rm -rf crawler_test_output
