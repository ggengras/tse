#!/bin/sh

# indextest.sh
# Graeme Gengras April, 2018
#
# indextest.sh is a shell script for performing integration
# testing on indexer.c.
#
# Run with ./indextest.sh or with `make test` in the indexer directory
#
#

TESTDIR="indexer_test_output"
EXEC="./indexer"

# Make sure everything is compiled (in case not run with `make test`)
if [ ! -d "$EXEC" ]
then
    make all
fi

cd ../crawler; make;
cd ../indexer

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

# Test index file creation (indexer)
./indexer $TESTDIR/wiki_crawl $TESTDIR/wiki_crawl_index

# Test index file copying (indextest)
./indextest $TESTDIR/wiki_crawl_index $TESTDIR/wiki_crawl_index_copy

# Sort files and check for differences
gawk -f indexsort.awk $TESTDIR/wiki_crawl_index > $TESTDIR/wiki_crawl_index.sorted
gawk -f indexsort.awk $TESTDIR/wiki_crawl_index_copy > $TESTDIR/wiki_crawl_index_copy.sorted
diff $TESTDIR/wiki_crawl_index.sorted $TESTDIR/wiki_crawl_index_copy.sorted &>/dev/null

if [ $? != 0]
then
    echo "Index file copying failed"
fi
