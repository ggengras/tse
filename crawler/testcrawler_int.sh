#!/bin/sh

# testcrawler_int.sh
# Graeme Gengras April, 2018
#
# testcrawler.sh is a shell script for performing integration
# testing on crawler.c.
#
# Run with ./testcrawler_int.sh or with `make test` in the crawler directory
#

DATE=`date '+%Y%m%d.%H%M%S'` # Record time that script is run (almost)
TESTDIR="crawler_test_output"
EXEC="./crawler"

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

##### Argument Tests #####
mkdir $TESTDIR/argtest
touch $TESTDIR/dummy

./crawler 2>&1 1>/dev/null | grep \
'Usage: ./crawler seedURL pageDirectory maxDepth' &> /dev/null
if [ $? != 0 ]; then
   echo "Arg Test 1 Failed"
fi

./crawler myServer bad_directory 3 \
    2>&1 1>/dev/null | grep 'Error reading directory' &> /dev/null
if [ $? != 0 ]; then
   echo "Arg Test 2 Failed"
fi

./crawler myServer $TESTDIR/dummy 3 \
    2>&1 1>/dev/null | grep 'Invalid directory' &> /dev/null
if [ $? != 0 ]; then
   echo "Arg Test 3 Failed"
fi

./crawler http://old-www.cs.dartmouth.edu/ $TESTDIR/argtest -5 \
    2>&1 1>/dev/null | grep 'Max depth must be an integer >= 0' &> /dev/null
if [ $? != 0 ]; then
   echo "Arg Test 4 Failed"
fi

./crawler http://old-www.cs.dartmouth.edu/ $TESTDIR/argtest apple \
    2>&1 1>/dev/null | grep 'Max depth must be an integer >= 0' &> /dev/null
if [ $? != 0 ]; then
   echo "Arg Test 5 Failed"
fi

rm $TESTDIR/dummy

##### Invalid Server Tests #####
mkdir $TESTDIR/servertest

# Test non-existent server
./crawler whereAmI? $TESTDIR/servertest 3 \
    2>&1 1>/dev/null | grep 'Error connecting to seedURL' &> /dev/null
if [ $? != 0 ]; then
   echo "Server Test 1 Failed"
fi

# Test non-internal server
./crawler http://www.example.com $TESTDIR/servertest 3 \
    2>&1 1>/dev/null | grep 'seedURL non-internal' &> /dev/null
if [ $? != 0 ]; then
   echo "Server Test 2 Failed"
fi

# Test non-existent page
./crawler http://old-www.cs.dartmouth.edu/beans $TESTDIR/servertest 3 \
    2>&1 1>/dev/null | grep 'Error connecting to seedURL' &> /dev/null
if [ $? != 0 ]; then
   echo "Server Test 3 Failed"
fi


##### Valid Server Tests #####
# These results require manual inspection

# Crawl http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/
# with depths 0-5
for i in $(seq 0 5)
do
    mkdir $TESTDIR/servertest/test1_depth$i
    echo Crawl results for \
        URL:http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ \
        with depth $i > $TESTDIR/servertest/test1_depth$i/README
    ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/ \
        $TESTDIR/servertest/test1_depth$i $i
done

# Crawl http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
# with depths 0-5
for i in $(seq 0 5)
do
    mkdir $TESTDIR/servertest/test2_depth$i
    echo Crawl results for \
        URL:http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html \
        with depth $i > $TESTDIR/servertest/test2_depth$i/README
    ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html \
        $TESTDIR/servertest/test2_depth$i $i
done

# Crawl http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia
# with depths 0-1 (depth 2 takes hours to run)
for i in $(seq 0 1)
do
    mkdir $TESTDIR/servertest/test3_depth$i
    echo Crawl results for \
        URL:http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ \
        with depth $i > $TESTDIR/servertest/test3_depth$i/README
    ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ \
        $TESTDIR/servertest/test2_depth$i $i
done
