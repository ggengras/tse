# Common
## Graeme Gengras, April, 2018

This directory contains functionality utilized by `crawler`, `indexer` and `querier`
that was not included in `libcs50`.  Some of the code is mine, some was provided to me
(noted in the files).

`file.h` contains functions for reading text files

`glib.h` is an assortment of helpful functions that I use in most projects

`index.h` contains functions for manipulating inverted indexes

`pagedir.h` contains functions for saving / loading crawler directories

`word.h` contains one function for "normalizing" words

### Compiling
Running `make` creates `libcommon.a` which you can then include when compiling
other code.  Run `make clean` to clean.
