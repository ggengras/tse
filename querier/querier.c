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

// Function declarations
int validateInput(char *input);
void wordSplit(char *input, char **words, int numWords);

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
    index_t *index = indexNew(500); // Hardcoded index length for now
    indexLoad(index, indexFile);

    // Retrieve a query
    char *input;
    while ((int)(input = readlinep(stdin)) != EOF) { // MALLOCS SPACE!
        // split into words

        int numWords = validateInput(input);
        if (numWords == 0) {
            printf("Error: query is empty or contains invalid characters.\n");
            continue;
        }
        printf("numWords %d\n", numWords);

        // Allocate word array accordingly
        char *words[numWords];
        assert(words != NULL);

        // Make array of words in input
        wordSplit(input, words, numWords); // MALLOCS

        printf("Evaluating query: ");
        for (int i = 0; i < numWords; i++) {
            printf("%s ", words[i]);
        }
        printf("\n");

        // figure out what query means

        // search

        // return results

        free(input);
    }

    return 0;
}

/*
 * validateInput -
 */
int validateInput(char *input) {
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
