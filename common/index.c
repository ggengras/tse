/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* index.c -
*/

#include <stdlib.h>
#include "index.h"
#include "file.h"
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

void saveHelperCounters(void *arg, const int key, int count) {
    FILE *fp = arg; // Cast void* to FILE*

    // Print docID, count pairs
    fprintf(fp, "%d %d ", key, count);

}

void saveHelperHashtable(void *arg, const char *word, void *counter) {
    FILE *fp = arg; // Cast void* to FILE*
    counters_t *counterCast = counter; // Cast void* to counters_t*

    fprintf(fp, "%s ", word);
    counters_iterate(counterCast, fp, (*saveHelperCounters));
    fprintf(fp, "\n"); // Newline for next word
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
 */
void loadIndex(index_t *index, FILE *fp)
{
    if (fp != NULL) {
        char *word = NULL;
        int docID = 0;
        int count = 0;
        for (int i = 0; i < lines_in_file(fp); i++) {
            word = readwordp(fp); // mallocs
            while (fscanf(fp, "%d %d ", &docID, &count)) {
                indexSet(index, word, docID, count);
            }
        }
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
    if (fp != NULL) {
        hashtable_iterate(index->ht, fp, (*saveHelperHashtable));
    } else {
        return false;
    }
}
