/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* index.h - Implements an inverted index that maps words to (docID, count)
* pairs.  Includes basic functions for incrementing and setting counts as
* well as saving the indexes to and loading them from files.
*/

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>
#include "counters.h"

// * * * * * * * * Global Types * * * * * * * * //
typedef struct index index_t;

// * * * * * * * * Local Functions * * * * //

/* Function to pass to hashtable_delete that deletes counter structs
 *
 * item is a pointer to a counter
 */
void deleteHelper(void *item);

/* Function to pass to hashtable_iterate that prints
 * the index file
 *
 * arg is the file pointer to print to, key is the word and
 * item is a pointer to a counter
 */
void saveHelperHashtable(void *arg, const char *key, void *item);

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

/* Returns the item associated with the given word.
 * Returns NULL if it can't find the word or the index is NULL
 */
counters_t *indexGet(index_t *index, const char *word);

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
 */
void indexLoad(index_t *index, FILE *fp);

/* Takes an `index` data structure and writes
 * it to a file
 *
 * Pointers must be non-NULL
 *
 * Returns `true` if successful, else `false`
 */
bool indexSave(index_t *index, FILE *fp);

#endif //__INDEX_H
