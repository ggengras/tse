# Testing crawler.c
## Graeme Gengras, April 2018

To test `crawler.c`, I wrote a shell script `testcrawler_int.sh` to perform
integration testing (making sure `crawler.c `does what it is supposed to do
given a wide range of input).  See `testcrawler_int.sh` for exact test cases.

I decided that unit testing was not necessary because of the simplicity of
`crawler.c`.  `crawler` and `pageSaver` are the only two functions, so
proper integration testing should be enough to ensure functionality of
everything in `crawler.c`.

### Test Cases
The testing encompasses invalid arguments, invalid seedURLs (dead servers,
nonexistent pages ...), and a number of different successful executions whose
results can be verified manually in `crawler_test_output`.
