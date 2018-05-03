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

.PHONY: test clean

test: $(PROG)
	echo Running Integration Tests
	./testcrawler_int.sh

clean:
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f $(PROG)
	rm -rf crawler_test_output
