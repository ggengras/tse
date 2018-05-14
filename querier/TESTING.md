# Testing querier.c
## Graeme Gengras, May 2018

To test `querier.c`, I wrote a shell script `queriertest.sh`.  The script crawls
a website to generate a directory of output from `crawler.c` and creates an index
file from the output using `indexer.c`.  Then, a number of valid and invalid queries
are used as input.  Currently, checking the validity of the results must be done manually.

Run tests with `make test`.
