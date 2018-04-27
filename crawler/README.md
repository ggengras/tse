# Web Crawler for TSE
## Graeme Gengras, April 2018

See `IMPLEMENTATION.md` for implementation details and `TESTING.md` for details of my testing process.
### Crawler:

### Usage:
Run crawler with `./crawler seedURL pageDirectory maxDepth` where `seedURL` is the
website to crawl, `pageDirectory` is an existing empty directory to store results in,
and `maxDepth` is the number of levels deep to crawl the `seedURL`. See examples below:

```bash
Put example shell output here
```

### Assumptions:
- Directory exists and is writable (but does basic checks)
- Directory is empty
- If maxDepth is a number, it is an integer (doesn't handle floats, etc.)

### Return Values:
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
