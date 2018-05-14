# Querier for TSE
## Graeme Gengras, May 2018

## Querier
`querier.c` uses a directory containing output from `crawler.c` and an associated
index file created by `indexer.c` to parse queries from the user.  The querier
returns a list of documents / webpages that satisfy the given query.

Still has some memory leaks (deadlines ...)

For instance:

```
[Query]: Dartmouth College
Evaluating query: dartmouth college
Matches 3 documents (ranked):
Score: 242 docID:   4 | http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
Score:   1 docID:   1 | http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
Score:   1 docID:   7 | http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html
```

### Compilation
Compile with `make`, clean the `querier` directory with `make clean`,
run tests with `make test`.  Compilation can also be done directly from the shell
if the necessary libraries have been built:

``` bash
gcc -o querier querier.c -Wall -pedantic -std=c11 -ggdb -I ../common -L ../common -lcommon -I ../libcs50 -L ../libcs50 -lcs50
```

### Usage
#### Querier
Run with ./querier pageDirectory indexFilename where `pageDirectory` is output from
`crawler.c` and `indexFilename` is the name of an index file created from `pageDirectory`
by `indexer.c`.

### Assumptions
- `pageDirectory` was created by `crawler.c`
- `indexFilename` was created by `indexer.c` from `pageDirectory`

### Return Values
- **0**: Success
- **1**: Incorrect number of arguments
- **2**: Invalid crawler output directory or invalid index file
- **3**: Error opening file for I/O
