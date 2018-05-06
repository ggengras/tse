#!/bin/sh

# indextest.sh
# Graeme Gengras April, 2018
#
# indextest.sh is a shell script for performing integration
# testing on indexer.c.
#
# Run with ./indextest.sh or with `make test` in the indexer directory
#

TESTDIR="indexer_test_output"
EXEC="./indexer"

# Make sure everything is compiled (in case not run with `make test`)
if [ ! -e "$EXEC" ]
then
    make all
fi

# If testdir exists remove it and make a fresh copy
if [ -e "$TESTDIR" ]
then
    if [ ! -w $TESTDIR ]
    then
        echo $TESTDIR is not writable
        exit 1
    fi

    rm -rf $TESTDIR
fi
mkdir $TESTDIR
