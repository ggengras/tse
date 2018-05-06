# Testing indexer.c
## Graeme Gengras, April 2018

To test `indexer.c`, I wrote a shell script `indextest.sh`.  The script crawls
a website to generate a directory of output from `crawler.c`, creates an index
file from the output, and then copies that index file with `indextest.c`.  The
two index files are then compared (and should be exactly the same).

Run tests with `make test`.


**Note**: `indextest.sh` uses a command `gawk` that might not come preinstalled
on all UNIX machines.
