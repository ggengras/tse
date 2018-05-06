/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* indexer.c -
*/

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include "file.h"
#include "index.h"
#include "pagedir.h"
#include "glib.h"

// * * * * * * * * Function Declarations * * * * * * * * //
//          See implementation section for details       //

int main(int argc, char *argv[])
{
    // Parse the command line, validate parameters
    // Check for # of args
    if (argc != 3) {
        fprintf(stderr, "Usage: ./indexer pageDirectory indexFilename\n");
        exit(1);
    }

    // Check for presence of `.crawler` file in `pageDirectory`
    char *pageDirectory = argv[1];
    char *dirTest = "/.crawler";
    char *filename = strCat(pageDirectory, dirTest); // Mallocs space!

    if (filename == NULL) { // Make sure alloc worked properly
        fprintf(stderr, "Error: Failed to allocate filename for ./crawler\n");

        // Clean up
        free(filename); // From strCat
        exit(10);
    }

    FILE *crawlerCheck;
    if ( (crawlerCheck = fopen(filename, "r")) == NULL ) {
        fprintf(stderr,
            "Error: Specified directory does not contain valid crawler output\n");

        // Clean up
        free(filename);
        fclose(crawlerCheck);
        exit(2);
    }

    // Clean up
    free(filename); // From strCat
    fclose(crawlerCheck);

    // Read files from crawler output into the index
    index_t *index = indexNew(500); // Number of hashtable slots is hardcoded atm

    // Create initial filename to open
    int fileNum = 1;
    char *fileNumStr;
    asprintf(&fileNumStr, "/%d", fileNum); // Mallocs space!
    char *crawlerFilename = strCat(pageDirectory, fileNumStr); // First file
    FILE *inputFile = fopen(crawlerFilename, "r");

    // Iterate over files in pageDirectory
    while (inputFile != NULL) {
        // Skip the first two lines of the file (find a better way to do this)
        char *input = readlinep(inputFile);
        free(input);
        input = readlinep(inputFile);
        free(input);

        while ( (input = readwordp(inputFile)) != NULL) {
            indexAdd(index, input, fileNum); // Add word to the index
        }

        // Not sure if this is necessary but why not
        free(input);
        free(fileNumStr);
        free(crawlerFilename);
        fclose(inputFile);

        // Go to next file
        fileNum += 1;
        asprintf(&fileNumStr, "/%d", fileNum);
        crawlerFilename = strCat(pageDirectory, fileNumStr);
        inputFile = fopen(crawlerFilename, "r");
    }
    // Need this one more time
    // Don't need to close FP bc it should be NULL at this point
    free(input);
    free(fileNumStr);
    free(crawlerFilename);

    // Create `indexFilename`, overwrite if it exists
    FILE *outputFile;
    if ( (outputFile = fopen(argv[2], "w")) == NULL ) {
        fprintf(stderr,
            "Error: Cannot open %s\n", argv[2]);
        exit(3);
    }

    // Write to file
    indexSave(index, outputFile);
    indexDelete(index);
}
