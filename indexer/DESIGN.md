# indexer.c Design
## Graeme Gengras, April 2018

Design Specifications for `indexer.c`.

The job of the `indexer` is to read the documents in the `pageDirectory` output by the `crawler`, build an inverted index mapping from words to documents, and write that index to a file.

The inverted index is implemented using the `hasthtable`, `set`, and `counters` data types and is structured in a way depicted by the image below:

![alt text](http://www.cs.dartmouth.edu/~cs50/Lectures/indexer/data-model.png "Logo Title Text 1")

The basic design of the indexer is as follows:
1. Process and validate command-line parameters
2. Initialize data structure index
3. index_build(directory, index)
4. index_save(file, index);
5. clean up data structures
