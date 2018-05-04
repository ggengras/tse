/*
* set.c   Graeme Gengras, April 2018
*
* CS50 'set' module
* see set.h for more information
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

/**************** local types ******************/
typedef struct setpair { // Using static throws an error
    char *key;
    void *item;
    struct setpair *next;
} setpair_t;

/**************** global types *****************/
typedef struct set {
    struct setpair *head;
} set_t;

/**************** local functions **************/
setpair_t *setpair_new(char *key, void *item)
{
    setpair_t *pair = malloc(sizeof(setpair_t));

    if (pair == NULL) {
        return NULL; // Memory not properly allocated
    } else {
        pair->key = key;
        pair->item = item;
        return pair;
    }
}

/**************** global functions **************/
set_t *set_new(void)
{
    set_t *set = malloc(sizeof(set_t));

    if (set == NULL) {
        return NULL; // Memory was not properly allocated
    } else {
        set->head = NULL; // Set is initialized empty
        return set;
    }
}

bool set_insert(set_t *set, const char *key, void *item)
{
    if (set != NULL && item != NULL && key != NULL) {
        // Need to copy key to not discard const qualifier
        char *keycpy = malloc(strlen(key) + 1);
        strcpy(keycpy, key);

        setpair_t *new = setpair_new(keycpy, item); // New key/value pair

        // Make sure key doesn't already exist
        if (set_find(set, keycpy) == NULL) {
            // Add new items to the head
            new->next = set->head;
            set->head = new;
            return true;
        }
    }
    return false;
}

void *set_find(set_t *set, const char *key)
{
    if (set != NULL && key != NULL) {
        for(setpair_t *pair = set->head; pair != NULL; pair = pair->next) {
            if (strcmp(key, pair->key) == 0) {
                return pair->item;
            }
        }
    }
    return NULL;
}

void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item) )
{
    if (fp != NULL) {
        if (set != NULL) {
            fputc('{', fp);
            // Iterate over set
            for (setpair_t *pair = set->head; pair != NULL; pair = pair->next) {
                // Print current node (key, item)
                if (itemprint != NULL) {
                    (*itemprint)(fp, pair->key, pair->item);

                    // Fixes comma at end of list
                    if (pair->next != NULL) {
                        fputc(',', fp);
                    }
                }
            }
            fputc('}', fp);
            fputs("\n", fp);
        } else {
            fputs("(NULL)\n", fp);
        }
    }
}

void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) )
{
    if (set != NULL && itemfunc != NULL) {
        // Call itemfunc with arg on each item
        for (setpair_t *pair = set->head; pair != NULL; pair = pair->next) {
            (*itemfunc)(arg, pair->key, pair->item);
        }
    }
}

void set_delete(set_t *set, void (*itemdelete)(void *item))
{
    if (set != NULL) {
        for (setpair_t *pair = set->head; pair != NULL;) {
            if (itemdelete != NULL) {
                (*itemdelete)(pair->item);
            }
            setpair_t *next = pair->next; // Store next pair
            free(pair->key);
            free(pair);
            pair = next; // Iterate
        }
        free(set);
    }
}
