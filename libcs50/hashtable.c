/*
* hashtable.c  Graeme Gengras, April 2018
*
* A `hashtable` is an array of slots, the size of which
* is determined by the modulus of the hashing function.
* It stores (`key`:`item`) pairs just like a `set`,
* but has a much faster lookup time because the hashing function
* maps each key to a known slot in the list.  Hashing is done using
* the Jenkins Hashing function - see `jhash.[ch]` for more details.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "jhash.h"
#include "set.h"

typedef struct hashtable {
    set_t **slots; // Hashtable is an array of pointers to sets
    int num_slots;
} hashtable_t;

hashtable_t *hashtable_new(const int num_slots)
{
    // Hashtable must have at least one slot
    if (num_slots > 0) {
        // Allocate memory for hashtable
        hashtable_t *hashtable = malloc(sizeof(hashtable_t));

        // Scale the size of the hashtable according to num_slots
        hashtable->slots = calloc(num_slots, sizeof(set_t*));
        hashtable->num_slots = num_slots;

        // Create an empty set in each slot
        for (int i = 0; i < num_slots; i++) {
            hashtable->slots[i] = set_new();
        }

        // Make sure memory was properly allocated
        if (hashtable == NULL || hashtable->slots == NULL) {
            return NULL;
        }
        return hashtable;
    } else {
        return NULL; // If invalid table length
    }
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item)
{
    if (ht != NULL && key != NULL && item != NULL) {
        // JenkinsHash takes unsigned longs but we are getting ints from the user
        // so pass ints and have it cast them for us
        int slot = JenkinsHash(key, ht->num_slots);
        return set_insert(ht->slots[slot], key, item);
    } else {
        return false;
    }
}

void *hashtable_find(hashtable_t *ht, const char *key)
{
    if (ht != NULL && key != NULL) {
        // Hash key
        int slot = JenkinsHash(key, ht->num_slots);

        // Go to key slot, search set in case of collisions
        return set_find(ht->slots[slot], key);
    } else {
        return NULL;
    }
}

void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item))
{
    if (fp != NULL) {
        if (ht != NULL) {
            // Iterate over slots
            for (int i = 0; i < ht->num_slots; i++) {
                // Print each set
                fprintf(fp, "Slot %d:", i);
                set_print(ht->slots[i], fp, (*itemprint));

            }
        } else {
            fputs("(NULL)\n", fp);
        }
    }
}

void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item))
{
    if (ht != NULL && itemfunc != NULL) {
        // Iterate over slots
        for (int i = 0; i < ht->num_slots; i++) {
            // Iterate over set in slot
            set_iterate(ht->slots[i], arg, (*itemfunc));
        }
    }
}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item))
{
    if (ht != NULL) {
        // Iterate over slots
        for (int i = 0; i < ht->num_slots; i++) {
            // Free the sets
            set_delete(ht->slots[i], (*itemdelete));
        }
        // Free memory sets were kept in
        free(ht->slots);
        free(ht);
    }
}
