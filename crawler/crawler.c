/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "webpage.h"
#include "bag.h"
#include "hashtable.h"

// * * * * * * * * Function Declarations * * * * * * * * //
//          See implementation section for details       //

int crawler(char *seedURL, char *pageDirectory, int maxDepth);
void pageSaver(webpage_t *page, char *pageDirectory, int ID);
void webpageDelete(void *item);
void urlDelete(void *item);
void strPrint(FILE *fp, void *item);

int main(int argc, char *argv[])
{
    // Parse the command line, validate parameters
    // Check for # of args
    if (argc != 4) {
        fprintf(stderr, "Usage: ./crawler seedURL pageDirectory maxDepth\n");
        exit(1);
    }

    // No need to check URL validity here, will be done by crawler
    // Make sure directory is valid (assumed to exist already)
    struct stat dirStatus;

    if (stat(argv[2], &dirStatus) == -1) {
        fprintf(stderr, "Error reading directory\n");
        exit(2);
    }

    if (!S_ISDIR(dirStatus.st_mode) ) {
        fprintf(stderr, "Invalid directory\n");
        exit(3);
    }

    // Make sure maxDepth is an integer
    int maxDepth;

    if (sscanf(argv[3], "%d", &maxDepth) != 1) {
        fprintf(stderr, "Max depth must be an integer >= 0\n");
        exit(4);
    }

    // Make sure max depth is >= 0
    if (maxDepth < 0) {
        fprintf(stderr, "Max depth must be an integer >= 0\n");
        exit(5);
    }

    // Validate seedURL
    // Validate pageDirectory

    // Crawler will return exit codes
    return crawler(argv[1], argv[2], maxDepth);
}

// * * * * * * * * Function Implementation * * * * * * * * //

/* *
 * pageSaver -
 * page: webpage with non-NULL URL, depth, HTML
 * pageDirectory: existing directory to save files
 *
 *
 *
 *
 */
int crawler(char *seedURL, char *pageDirectory, int maxDepth)
{
    // Make a 'webpage' for the seedURL, depth 0, no HTML (yet)
    webpage_t *seedPage = webpage_new(seedURL, 0, NULL);

    // Initialize bag to store list of webpages to crawl
    bag_t *crawlList = bag_new();

    if (crawlList == NULL) {
        fprintf(stderr, "Error initializing bag\n");
        return 6;
    }

    // Initialize hashtable to store seen URLS
    // # of hashtable slots scales with maxDepth
    // assume an upper limit of ~100 links per webpage
    // This would be reasonable for most average sites
    // but not for many popular sites, reddit, news, etc.
    hashtable_t *seenURLS = hashtable_new(maxDepth * 100);

    // Add seedURL the bag of webpages to crawl
    bag_insert(crawlList, seedPage);

    // Add seedURL to hashtable of URLs seen
    hashtable_insert(seenURLS, seedURL, seedPage);

    if (seenURLS == NULL) {
        fprintf(stderr, "Error initializing hashtable\n");
        return 7;
    }

    // While there are more webpages to crawl
    // Take webpage from the bag of webpages
    webpage_t *currentPage = NULL;

    int id = 1; // store 'ID' of pages we crawl
    while ((currentPage = bag_extract(crawlList)) != NULL) {
        // pagefetch html for the URL AND pause for one second
        webpage_fetch(currentPage);

        // pagesave the webpage to pageDirectory with unique ID
        pageSaver(currentPage, pageDirectory, id);

        // If webpage depth < maxDepth find links
        if (webpage_getDepth(currentPage) < maxDepth) {
            int depth = webpage_getDepth(currentPage);
            int pos = 0;
            char *URL = NULL;
            while ((pos = webpage_getNextURL(currentPage, pos, &URL)) > 0) {
                // Normalize the URL, make sure it's internal to Dartmouth
                if (NormalizeURL(URL) && IsInternalURL(URL)) {
                    // Try to insert URL in hashtable
                    webpage_t *newPage = webpage_new(URL, depth + 1, NULL);
                    if (hashtable_insert(seenURLS, URL, newPage)) {
                        printf("%s\n", URL);
                        // Add new webpage to the bag of webpages to be crawled
                        bag_insert(crawlList, newPage);
                    }
                        // If it was already in hashtable do nothing
                }
                free(URL);
            }
        }
        id += 1; // Increment ID
    }


    // Clean up data structure
    hashtable_delete(seenURLS, webpageDelete);
    bag_delete(crawlList, webpageDelete);
    return 0;
}

/* *
 * pageSaver -----
 * Takes a webpage and saves it to a file called 'ID' in 'pageDirectory'
 *
 * Arguments -----
 * page: webpage with non-NULL URL, depth, HTML
 * pageDirectory: existing directory to save files
 * id: unique id # of page
 *
 *
 *
 */
void pageSaver(webpage_t *page, char *pageDirectory, int ID)
{
    // Convert ID to a string
    char *strID;
    asprintf(&strID, "%d", ID); // Mallocs space!!


    // Allocate memory for filename and write in form of 'pageDirectory/strID'
    char *filename = calloc(strlen(pageDirectory) + strlen(strID) + 2,
        sizeof(char));
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
}

/* *
 * webpageDelete -----
 *
 * Arguments -----
 * page: webpage with non-NULL URL, depth, HTML
 * pageDirectory: existing directory to save files
 *
 *
 *
 *
 */
void webpageDelete(void *item)
{

}

/* *
 * urlDelete -----
 *
 * Arguments -----
 * page: webpage with non-NULL URL, depth, HTML
 * pageDirectory: existing directory to save files
 *
 *
 *
 *
 */
void urlDelete(void *item)
{

}

/* *
 * strPrint -----
*
 * Arguments -----
 * page: webpage with non-NULL URL, depth, HTML
 * pageDirectory: existing directory to save files
 *
 *
 *
 *
 */
void strPrint(FILE *fp, void *item)
{
    int str = webpage_getDepth(item);
    printf("%d", str);
}
