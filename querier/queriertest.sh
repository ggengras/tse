#!/bin/sh

# querier.sh
# Graeme Gengras May, 2018
#
# queriertest.sh is a shell script for performing integration
# testing on querier.c.
#
# Run with ./queriertest.sh or with `make test` in the querier directory
#
#

TESTDIR="querier_test_output"
EXEC="./querier"

# Make sure everything is compiled (in case not run with `make test`)
if [ ! -d "$EXEC" ]
then
    make all
fi

cd ../crawler; make;
cd ../indexer; make;
cd ../querier

# If testdir exists remove it and make a fresh copy
if [ -d "$TESTDIR" ]
then
    if [ ! -w $TESTDIR ]
    then
        echo $TESTDIR is not writable
        exit 1
    fi

    rm -rf $TESTDIR
fi
mkdir $TESTDIR

# Create crawler output from the CS50 wikipedia site to test with
mkdir $TESTDIR/wiki_crawl
../crawler/crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ \
    $TESTDIR/wiki_crawl 1

# Create index file to test with
../indexer/indexer $TESTDIR/wiki_crawl $TESTDIR/wiki_crawl_index

cd querier_test_output
../querier wiki_crawl wiki_crawl_index < ../testqueries
