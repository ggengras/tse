/* 'Tiny' Search Engine
*  Graeme Gengras, May 2018
*
* querier.c -
*
*
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "index.h"
#include "pagedir.h"
#include "file.h"
#include "word.h"
#include "counters.h"

// Local types
typedef struct twoCounters { // So I can call counters_iterate with 3 counters
    counters_t *first;
    counters_t *second;
} twoCounters_t;

// Function declarations
int checkInputFormat(char *input);
int checkInputLogic(char **words, int numWords);
void wordSplit(char *input, char **words, int numWords);
counters_t *scoreDocuments(char **words, int numWords, index_t *index);
counters_t *intersectCounters(counters_t *wordOne, counters_t *wordTwo);
void intersectCountersHelper(void *arg, const int key, int count);
counters_t *unionCounters(counters_t *wordOne, counters_t *wordTwo);
void unionCountersHelper(void *arg, const int key, int count);

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
    if (!isCrawlerDir(pageDirectory)) {
        fprintf(stderr,
            "Error: Specified directory does not contain valid crawler output\n");
        exit(2);
    }

    // Load the index file
    int nLines = lines_in_file(indexFile);
    index_t *index = indexNew(nLines); // Hardcoded index length for now
    indexLoad(index, indexFile);

    // Retrieve a query
    char *input;
    while (1) {
        printf("[Query]: ");
        if ((int)(input = readlinep(stdin)) == EOF) { // MALLOCS SPACE!
            // exit if EOF
            free(input);
            break;
        }

        // Make sure input is valid
        int numWords = checkInputFormat(input);
        if (numWords == 0) {
            printf("Error: query is empty or contains invalid characters.\n");
            continue;
        }

        // Make array of words in input
        char *words[numWords];
        assert(words != NULL);

        wordSplit(input, words, numWords); // MALLOCS

        // Check input logic (make sure ands and ors are in correct locations)
        if (!checkInputLogic(words, numWords)) {
            printf("Error: query contains invalid logic\n");
            continue;
        }

        // Print clean query
        printf("Evaluating query: ");
        for (int i = 0; i < numWords; i++) {
            printf("%s ", words[i]);
        }
        printf("\n");

        // Create 'counters' object of all pertinent documents
        // Will consist of docID and a 'score'
        counters_t *queryScore = scoreDocuments(words, numWords, index); // MALLOCS

        // Rank results

        counters_delete(queryScore);
        free(input);
    }

    indexDelete(index);
    return 0;
}

/*
 * checkInputFormat - Checks format of input string.  If string is valid,
 * returns the number of words in the string.  If string is invalid
 * (blank space or has non-alpha characters) returns 0;
 */
int checkInputFormat(char *input) {
    // count non-alpha characters and spaces
    char *iteratorInvalid = input;
    int nonalpha = 0;
    int spaces = 0;

    while (*iteratorInvalid) {
        if (isspace(*iteratorInvalid)) {
            // If we see a space increment spaces
            spaces++;
        } else {
            if (!isalpha(*iteratorInvalid)) {
                // If we see a non-alpha non-space, it's a bad char
                nonalpha++;
                break;
            }
        }
        iteratorInvalid++;
    }

    if (nonalpha > 0 || spaces == strlen(input)) {
        // 0 Means bad input
        return 0;
    }

    // Figure out how many words are in the input
    char *iteratorWords = input;
    int numWords = 0;
    while (*iteratorWords != '\0') {
        // Find beginning of a word
        while (!isalpha(*iteratorWords)) {
            iteratorWords++;
        }
        // add word to length, catch empty queries
        if (isalpha(*iteratorWords)) {
            numWords++;
        }

        // Move to end of word, stop if we reach null
        while (isalpha(*iteratorWords) != 0 && *iteratorWords != '\0') {
            iteratorWords++;
        }
    }

    return numWords;
}


/*
 * checkInputLogic - Checks the placement of 'and' and 'or' in a list of words.
 * If the list can be evaluated logically, returns 1, if it can't returns 0.
 */
int checkInputLogic(char **words, int numWords) {
    // First word can't be logic
    if (strcmp(words[0], "and") == 0 || strcmp(words[0], "or") == 0 ) {
        return 0;
    }

    // Last word can't be logic
    if (strcmp(words[numWords - 1], "and") == 0
      || strcmp(words[numWords - 1], "or") == 0 ) {
        return 0;
    }

    // 'and' must have non-logic words on either side
    for (int i = 1; i < numWords - 1; i++) {
        if (strcmp(words[i], "and") == 0) {
            if (strcmp(words[i - 1], "and") == 0) {
                return 0;
            }
            if (strcmp(words[i - 1], "or") == 0) {
                return 0;
            }
            if (strcmp(words[i + 1], "and") == 0) {
                return 0;
            }
            if (strcmp(words[i + 1], "or") == 0) {
                return 0;
            }
        }
    }
    return 1;
}

/*
 * wordSplit - takes an input string and splits it into an array of words
 */
void wordSplit(char *input, char **words, int numWords) {
    // Start both iterators at beginning of string
    char *word = input;
    char *rest = input;
    for (int i = 0; i < numWords; i++) {
        // Move 'word' to beginning of first word
        while (!isalpha(*word)) {
            word++;
        }

        // Move 'rest' to char after first word
        rest = word;
        while (isalpha(*rest) != 0) {;
            rest++;
        }
        *rest = '\0';
        words[i] = NormalizeWord(word); // Add word to word array

        // Position pointers to find next word
        word = rest;
    }
}

/*
 * scoreDocuments -
 */
counters_t *scoreDocuments(char **words, int numWords, index_t *index) {
    counters_t *wordOne = indexGet(index, words[0]);
    counters_t *wordTwo = indexGet(index, words[1]);
    counters_t *result = unionCounters(wordOne, wordTwo);

    counters_print(result, stdout);
}

/*
 * intersectCounters - Finds the intersection of two counters (two words)
 * Takes a counter for each word.  Returns a NEW counter with the result.
 * This needs to be deleted!
 */
counters_t *intersectCounters(counters_t *wordOne, counters_t *wordTwo) {
    // Need this struct for for use w/ counters_iterate
    counters_t *result = counters_new();
    twoCounters_t *twoCounters = malloc(sizeof(twoCounters_t)); // MALLOCS
    twoCounters->first = wordOne;
    twoCounters->second = result;

    // Iterate over wordOne, see if docID is in wordTwo.
    counters_iterate(wordTwo, twoCounters, (*intersectCountersHelper));
    return twoCounters->second;

    free(twoCounters);
}

/*
 *  intersectCountersHelper - for use with intersectCounters / counters_iterate
 */
void intersectCountersHelper(void *arg, const int key, int count) {
    // Cast arg (is a counters_t *)
    twoCounters_t *twoCounters = arg;

    // If key is in wordOne, set the counter to the minumum of the two counts
    int oneCount = counters_get(twoCounters->first, key);
    printf("%d %d\n", count, oneCount);
    if (oneCount > 0) {
        if (count < oneCount) {
            counters_set(twoCounters->second, key, count);
        } else {
            counters_set(twoCounters->second, key, oneCount);
        }
    }
}

/*
 * unionCounters - Finds the union of two counters (two words)
 * Takes a counter for each word.  Returns a NEW counter with the result.
 * This needs to be deleted!
 */
counters_t *unionCounters(counters_t *wordOne, counters_t *wordTwo) {
    // Need this struct for for use w/ counters_iterate
    counters_t *result = counters_new();
    twoCounters_t *twoCounters = malloc(sizeof(twoCounters_t)); // MALLOCS
    twoCounters->first = wordOne;
    twoCounters->second = result;

    // Iterate over wordOne, see if docID is in wordTwo.
    // Iterate twice because we need to collect ALL docIDs in both counters
    counters_iterate(wordTwo, twoCounters, (*unionCountersHelper));
    counters_iterate(wordOne, twoCounters, (*unionCountersHelper));

    return twoCounters->second;

    free(twoCounters);
}

/*
 *  unionCountersHelper - for use with unionCounters / counters_iterate
 */
void unionCountersHelper(void *arg, const int key, int count) {
    // Cast arg (is a counters_t *)
    twoCounters_t *twoCounters = arg;

    // If key is in wordOne, set the counter to the minumum of the two counts
    int oneCount = counters_get(twoCounters->first, key);
    if (oneCount > 0) {
        if (count < oneCount) {
            counters_set(twoCounters->second, key, count);
        } else {
            counters_set(twoCounters->second, key, oneCount);
        }
    } else {
        counters_set(twoCounters->second, key, count);
    }
}
