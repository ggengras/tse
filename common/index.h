/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* indexer.h - Implements an inverted index that maps words to (docID, count)
* pairs.  Includes basic functions for incrementing and setting counts as
* well as saving the indexes to and loading them from files.
*/

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>

// * * * * * * * * Global Types * * * * * * * * //
typedef struct index index_t;

// * * * * * * * * Local Functions * * * * //

/*
 * indexDelete needs a litte help
 */
void deleteHelper(void *item);

// * * * * * * * * Function Declarations * * * * //

/* Creates a new index with the specified number of hashtable slots
 *
 * num_slots must be a positive integer
 *
 * Returns `true` if successful, else `false`
 */
index_t *indexNew(const int num_slots);

/* Increments the counter associated with the given word and docID
 * If the counter does not exist, creates a new one
 *
 * docID must be a positive integer, word, index must be non-NULL
 *
 * If unsuccessful or incorrect arguments nothing happens
 */
void indexAdd(index_t *index, const char *word, const int docID);

/* Sets the counter associated with the given word and docID
 * If the counter does not exist, creates a new one
 *
 * docID, count must be positive integers, word, index must be non-NULL
 *
 * If unsuccessful or incorrect arguments nothing happens
 */
void indexSet(index_t *index, const char *word, const int docID, int count);

/* Delete the given index and clean up all allocated memory
 *
 * Ignore NULL indexes
 */
void indexDelete(index_t *index);

/* Takes an index file (written by saveIndex, or of the same
 * format) and loads it into an `index` data structure
 *
 * Returns a pointer to dynamically allocated memory
 * containing the index
 *
 * If unsuccessful will return NULL pointer
 */
index_t *loadIndex(FILE *fp);

/* Takes an `index` data structure and writes
 * it to a file
 *
 * Pointers must be non-NULL
 *
 * Returns `true` if successful, else `false`
 */
bool saveIndex(index_t *index, FILE *fp);

#endif //__INDEX_H
