/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* indexer.c - Takes a directory of output from crawler.c and creates an
* index file that conatins information about how often different words occur
* on each page.
*/

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "file.h"
#include "index.h"
#include "pagedir.h"
#include "glib.h"
#include "webpage.h"

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
    if (!isCrawlerDir(pageDirectory)) {
        fprintf(stderr,
            "Error: Specified directory does not contain valid crawler output\n");
        exit(2);
    }

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
        // Read file into a webpage data type
        char *url = readlinep(inputFile);
        char *depthStr = readlinep(inputFile);
        char *html = readfilep(inputFile);

        int depth = atoi(depthStr); // Cast depth to int
        webpage_t *currentPage = webpage_new(url, depth, html);

        free(url);
        free(depthStr);
        // Can't free HTML yet because only the pointer is copied

        char *word;
        int pos = 0;
        while ((pos = webpage_getNextWord(currentPage, pos, &word)) > 0) { // MALLOCS
            indexAdd(index, word, fileNum); // Add word to the index
            free(word);
        }

        //free(html);
        free(fileNumStr);
        free(crawlerFilename);
        //free(word);
        fclose(inputFile);
        webpage_delete(currentPage);

        // Go to next file
        fileNum += 1;
        asprintf(&fileNumStr, "/%d", fileNum);
        crawlerFilename = strCat(pageDirectory, fileNumStr);
        inputFile = fopen(crawlerFilename, "r");
    }
    // Need this one more time
    // Don't need to close FP bc it should be NULL at this point
    free(fileNumStr);
    free(crawlerFilename);

    // Create `indexFilename`, overwrite if it exists
    FILE *outputFile;
    if ( (outputFile = fopen(argv[2], "w")) == NULL ) {
        fprintf(stderr,
            "Error: Cannot open %s\n", argv[2]);
        // Clean up
        indexDelete(index);
        fclose(outputFile);
        exit(3);
    }

    // Write to file
    indexSave(index, outputFile);
    indexDelete(index);
    fclose(outputFile);
    return 0;
}
