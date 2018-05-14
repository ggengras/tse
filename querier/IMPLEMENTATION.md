# querier.c Implementation
## Graeme Gengras, May 2018

### Algorithm
The querier follows the basic logic detailed below:

1. execute from a command line

2. parse arguments

3. load provided index file into internal data structure

4. prompt the user for a query

5. split query into individual words, parse for validity

6. search the index for documents that satisfy the query

7. rank the results by 'score'

8. display results

### Output Format
If matching documents are found, the querier displays the number of matching documents followed by a list of the documents.  The list shows the score, document ID, and associated URL.

Example output:

```
[Query]: Dartmouth College
Evaluating query: dartmouth college
Matches 3 documents (ranked):
Score: 242 docID:   4 | http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Dartmouth_College.html
Score:   1 docID:   1 | http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/
Score:   1 docID:   7 | http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/wiki/Computer_science.html

```
