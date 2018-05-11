/* 'Tiny' Search Engine
*  Graeme Gengras, May 2018
*
* querier.c -
*
*
*/

#include <stdio.h>
#include "index.h"
#include "pagedir.h"
#include "file.h"

// Function declarations
    // find words in string


int main(int argc, char *argv[]) {
    // Parse the command line, validate parameters
    // Check for # of args
    if (argc != 3) {
        fprintf(stderr, "Usage: ./querier pageDirectory indexFilename\n");
        exit(1);
    }

    // Try to open indexFilename
    char *indexFilename = argv[2];
    FILE *indexFile;
    if ( (indexFile = fopen(indexFilename, "r")) == NULL ) {
        fprintf(stderr,
            "Error: Cannot open %s\n", indexFilename);
        fclose(indexFile);
        exit(2);
    }

    // Make sure pageDirectory is valid crawler output
    char *pageDirectory = argv[1];
    if(!isCrawlerDir(pageDirectory)) {
        fprintf(stderr,
            "Error: Specified directory does not contain valid crawler output\n");
        exit(2);
    }

    // Load the index file
    index_t *index = indexNew(500); // Hardcoded index length for now
    indexLoad(index, indexFile);

    // Retrieve a query
    char *input;

    while( (input = readlinep(stdin)) != EOF) { // MALLOCS SPACE!
        

    }

    return 0;
}
