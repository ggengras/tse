/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* index.c -
*/

#include <stdlib.h>
#include "index.h"
#include "hashtable.h"
#include "counters.h"

// * * * * * * * * Global Types * * * * * * * * //
typedef struct index {
    hashtable_t *ht;
    int num_slots;
} index_t;

// * * * * * * * * Local Functions * * * * //

void deleteHelper(void *item) {
    counters_t *ctr = item;
    counters_delete(ctr);
}

// * * * * * * * * Function Implementation * * * * //

index_t *indexNew(const int num_slots)
{
    index_t *index = malloc(sizeof(index_t)); // Malloc
    index-> ht = hashtable_new(num_slots); // Malloc
    index->num_slots = num_slots;
}

void indexAdd(index_t *index, const char *word, const int docID)
{
    if (index != NULL && word != NULL && docID >= 0) {
        // Look up the LIST of counters we want (for the given word)
        counters_t *counter = hashtable_find(index->ht, word);

        if (counter != NULL) { // If there is an entry there
            // Increment the counter at the specified docID
            counters_add(counter, docID);
        } else {
            // Or else we need to make one
            counters_t *new_counter = counters_new(); // Malloc
            counters_add(new_counter, docID);
            hashtable_insert(index->ht, word, new_counter);
        }
    }
}

void indexSet(index_t *index, const char *word, const int docID, int count)
{
    if (index != NULL && word != NULL && docID >= 0) {
        // Look up the LIST of counters we want (for the given word)
        counters_t *counter = hashtable_find(index->ht, word);

        if (counter != NULL) { // If there is an entry there
            // Increment the counter at the specified docID
            counters_set(counter, docID, count);
        } else {
            // Or else we need to make one
            counters_t *new_counter = counters_new(); // Malloc
            counters_set(new_counter, docID, count);
            hashtable_insert(index->ht, word, new_counter);
        }
    }
}

void indexDelete(index_t *index)
{
    hashtable_delete(index->ht, (*deleteHelper));
    free(index->ht);
}


/* Takes an index file (written by saveIndex, or of the same
 * format) and loads it into an `index` data structure
 *
 * Returns a pointer to dynamically allocated memory
 * containing the index
 *
 * If unsuccessful will return NULL pointer
 */
index_t *loadIndex(FILE *fp)
{
    FILE *fp;
    if ( (fp = fopen(filename, "r")) == NULL ) {
        char c = '\0' // Char to store 

        while ((c = fgetc()))



    } else {
        return NULL;
    }
}

/* Takes an `index` data structure and writes
 * it to a file
 *
 * Pointers must be non-NULL
 *
 * Returns `true` if successful, else `false`
 */
bool saveIndex(index_t *index, FILE *fp)
{

}
