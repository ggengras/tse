# Indexer for TSE
## Graeme Gengras, April 2018

### Indexer
`indexer.c` takes a directory containing output from `crawler.c`
and creates an index file that lists all of the words found on pages in the crawler directory.
Each line of the index is a word followed by a list of (docID, count) pairs that
indicate which documents the word appears in and how many times it is used.

For instance:

```
...
b 4 1
tse 1 1 3 1
cs50 1 1 3 1
...
```

### Indextest
`indextest.c` takes a preexisting index file, reads it into an index data structure
and then writes the index to a new file.  If all goes well, the two files should be
identical.

### Compilation
Compile with `make`, clean the `indexer` directory with `make clean`,
run tests with `make test`.  Compilation can also be done directly from the shell
if the necessary libraries have been built:

``` bash
gcc -o indexer indexer.c -Wall -pedantic -std=c11 -ggdb -I ../common -L ../common -lcommon -I ../libcs50 -L ../libcs50 -lcs50
```

``` bash
gcc -o indextest indextest.c -Wall -pedantic -std=c11 -ggdb -I ../common -L ../common -lcommon -I ../libcs50 -L ../libcs50 -lcs50
```

### Usage
#### Indexer
Run with ./indexer pageDirectory indexFilename where `pageDirectory` is output from
`crawler.c` and `indexFilename` is the name of a file to write the index to.


#### Indextest
Run with ./indextest oldIndexFilename newIndexFilename where `oldIndexFilename`
is the name of an existing index file and `newIndexFilename` is is the name of a
file to write the index to.


### Assumptions
- `pageDirectory` was created by `crawler.c`

### Return Values
`indexer.c` and `indextest.c` share common exit codes:

- **0**: Success
- **1**: Incorrect number of arguments
- **2**: Invalid crawler output directory
- **3**: Error opening file for I/O
