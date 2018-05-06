# indexer.c Implementation
## Graeme Gengras, April 2018

### Algorithm
The indexer follows the basic logic detailed below:

1. execute from a command line

2. parse the command line, validate parameters, initialize other modules (index)

3. loop over files in `pageDirectory`. For each file:
    1. Skip the first two lines
    2. Read words, as each word is encountered add it to the index and increment
       the associated counter for the current document

4. create or overwrite `indexFilename`

5. save the index to `indexFilename`

6. clean up memory / close files

### Included Modules
`indexer.c` utilizes the `index` data structure which I created and is contained
in `index.h`.  I also include `file.h`, `pagedir.h`, and `glib.h` from the common
directory which contain functions for interacting with files / text.

### Output Format
The index file lists all of the words found on pages in the crawler directory.
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
