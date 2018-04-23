/* CS50 - Tiny Search Engine
*  Graeme Gengras, April 2018
*
*
*
*/

#include <stdio.h>
#include <unistd.h>
#include "webpage.h"
#include "bag.h"
#include "hashtable.h"

// * * * * * * * * Function Declarations * * * * * * * * //
//          See implementation section for details       //

int crawler(char *seedURL, char *pageDirectory, int maxDepth);
char *pageScanner(webpage_t *page);
void pageSaver(webpage_t *page);
void webpageDelete(void *item);
void urlDelete(void *item);
void strPrint(FILE *fp, void *item);

int main(int argc, char *argv[])
{
    // Parse the command line, validate parameters
    // Check for # of args
    if (argc != 4) {
        printf("Usage: ./crawler seedURL pageDirectory maxDepth\n");
        return 1;
    }

    // No need to check URL validity here, will be done by the crawler
    // Make sure directory exists

    // Make sure maxDepth is an integer
    int maxDepth = 0;

    if (sscanf(argv[3], "%d", &maxDepth) != 1) {
        fprintf(stderr, "Max depth must be an integer >= 0\n");
        return 1;
    }

    // Make sure max depth is >= 0
    if (maxDepth < 0) {
        fprintf(stderr, "Max depth must be an integer >= 0\n");
        return 1;
    }

    // Validate seedURL
    // Validate pageDirectory

    // Crawler will return exit codes
    return crawler(argv[1], argv[2], 0);
}

// * * * * * * * * Function Implementation * * * * * * * * //
int crawler(char *seedURL, char *pageDirectory, int maxDepth)
{
    // Make a 'webpage' for the seedURL, depth 0, no HTML (yet)
    webpage_t *seedPage = webpage_new(seedURL, 0, NULL);

    // Initialize bag to store list of webpages to crawl
    bag_t *crawlList = bag_new();

    if (crawlList == NULL) {
        fprintf(stderr, "Error initializing bag\n");
        return 2;
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

    // While there are more webpages to crawl
    // Take webpage from the bag of webpages
    webpage_t *currentPage = NULL;

    while ((currentPage = bag_extract(crawlList)) != NULL) {

        // Pause for one second, this is built into webpage fetch
        //sleep(1);

        // pagefetch html for the URL
        webpage_fetch(currentPage);

        // pagesave the webpage to pageDirectory with unique ID

        // If webpage depth < maxDepth find links

            // Pagescan the webpage to extract all URLS

            // For each URL

                // Normalize the URL

                // Ignore URL if not internal

                // Try to insert URL in hashtable

                    // If it was already in hashtable do nothing

                    // If it was added to the hashtable

                        // Make a new `webpage` for that URL at depth+1

                        // Add new webpage to the bag of webpages to be crawled
        return 0;
    }


    // Clean up data structure
    hashtable_delete(seenURLS, webpageDelete);

}

char *pageScanner(webpage_t *page)
{

}

void pageSaver(webpage_t *page)
{

}

void webpageDelete(void *item)
{

}

void urlDelete(void *item)
{

}

void strPrint(FILE *fp, void *item)
{
    int str = webpage_getDepth(item);
    printf("%d", str);
}
