/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* pagedir.c - A collection of functions for manipulating 'crawler' directories
*
* See pagedir.h for more information
*/

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include "pagedir.h"
#include "assert.h"
#include "string.h"
#include "glib.h"

// * * * * * * * * Function Declarations * * * * //

bool savePage(webpage_t *page, char *pageDirectory, int ID) {
    // Convert ID to a string
    char *strID;
    asprintf(&strID, "%d", ID); // Mallocs space!!
    assert(strID != NULL);

    // Allocate memory for filename and write in form of 'pageDirectory/strID'
    char *filename = calloc(strlen(pageDirectory) + strlen(strID) + 2,
        sizeof(char));
    assert(filename != NULL);

    strcpy(filename, pageDirectory);
    strcpy(filename + strlen(pageDirectory), "/");
    strcpy(filename + strlen(pageDirectory) + 1, strID);

    // Null terminate filename string
    filename[strlen(pageDirectory) + strlen(strID) + 1] = '\0';

    // Open file for writing
    FILE *outputFile = fopen(filename, "w");
    fprintf(outputFile, "%s\n", webpage_getURL(page));
    fprintf(outputFile, "%d\n", webpage_getDepth(page));
    fprintf(outputFile, "%s", webpage_getHTML(page));

    free(strID);
    free(filename);
    fclose(outputFile);
    return true;
}

bool isCrawlerDir(char *pageDirectory) {
    // Check for presence of `.crawler` file in `pageDirectory`
    char *dirTest = "/.crawler";
    char *filename = strCat(pageDirectory, dirTest); // Mallocs space!

    assert(filename != NULL);

    FILE *crawlerCheck;
    if ( (crawlerCheck = fopen(filename, "r")) == NULL ) {
        // Clean up
        free(filename);
        fclose(crawlerCheck);
        return false;
    } else {
        return true;
    }
}
