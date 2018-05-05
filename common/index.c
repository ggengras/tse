/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* index.c -
*/

#include <stdlib.h>
#include "index.h"
#include "word.h"
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
    fprintf(fp, "%s ", NormalizeWord(word));
    counters_iterate(counterCast, fp, (*saveHelperCounters));
    fprintf(fp, "\n"); // Newline for next word
}

// * * * * * * * * Function Implementation * * * * //

index_t *indexNew(const int num_slots)
{
    index_t *index = malloc(sizeof(index_t)); // Malloc
    index->ht = hashtable_new(num_slots); // Malloc
    index->num_slots = num_slots;
    return index;
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
    //free(index->ht); don't need this?
}

void indexLoad(index_t *index, FILE *fp)
{
    if (fp != NULL) {
        char *word = NULL;
        int docID = 0;
        int count = 0;
        int scan;
        while ( (word = readwordp(fp)) != NULL) {
            while ((scan = fscanf(fp, "%d %d ", &docID, &count)) > 0) {
                indexSet(index, NormalizeWord(word), docID, count);
            }
            free(word);
        }
    }
}

bool indexSave(index_t *index, FILE *fp)
{
    if (fp != NULL) {
        hashtable_iterate(index->ht, fp, (*saveHelperHashtable));
        return true;
    } else {
        return false;
    }
}
