# Web Crawler for TSE
## Graeme Gengras, April 2018

See `IMPLEMENTATION.md` for implementation details and `TESTING.md`
for details of my testing process.

### Crawler
A web crawler that, given a seedURL and output directory, will scrape the URL, its links, links on these linked pages,
etc. to a given maxDepth.  Output is a series of files representing each unique link seen by the crawler.  Each
file contains the URL, depth at which the URL was found, and html of the page.

### Compilation
Compile with `make`, clean the `crawler` directory with `make clean`,
run tests with `make test`.  Compilation can also be done directly from the shell
if the necessary libraries have been built:

```bash
gcc -o crawler crawler.c -Wall -pedantic -std=c11 -ggdb -I ../libcs50 -L ../libcs50 -lcs50 -I ../common -L ../common -lcommon
```

`libcs50` must be included as that contains `webpage.h`, `bag.h` and `hashtable.h`.

### Usage
Run crawler with `./crawler seedURL pageDirectory maxDepth` where `seedURL`
is the website to crawl, `pageDirectory` is an existing empty directory to store
results in, and `maxDepth` is the number of levels deep to crawl the `seedURL`. '
See example below of exectuion `./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html data 3`

```bash
Crawling http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html with depth 3 ...
0    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
0      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
0   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
0      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
1    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
1      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
1   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/A.html
1      Found: https://en.wikipedia.org/wiki/Algorithm
1  IgnExtern: https://en.wikipedia.org/wiki/Algorithm
1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
1      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
1    IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
2    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
2      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
2   Scanning: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/B.html
2      Found: https://en.wikipedia.org/wiki/Breadth-first_search
2  IgnExtern: https://en.wikipedia.org/wiki/Breadth-first_search
2      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
2      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
2      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
2      Found: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
2    IgnDupl: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
3    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
3      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/E.html
3    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
3      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html
3    Fetched: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
3      Added: http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/C.html
```

### Assumptions
- Directory exists and is writable (but does basic checks)
- Directory is empty
- If maxDepth is a number, it is an integer (doesn't handle floats, etc.)

### Return Values
- **0**: Success
- **1**: Incorrect number of arguments
- **2**: Error reading directory
- **3**: Invalid directory (a file is specified instead of a folder)
- **4**: Given depth is not an integer
- **5**: Given depth is not >= 0
- **6**: Error initializing bag data structure
- **7**: Error initializing hashtable data structure
- **8**: Error connecting to seedURL
- **9**: seedURL non-internal to the domain `http://old-www.cs.dartmouth.edu/`
- **10**: Memory allocation error (malloc returned NULL pointer)
