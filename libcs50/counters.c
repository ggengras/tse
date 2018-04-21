/*
* counters.c   Graeme Gengras, April 2018
*
* CS50 'counters' module
* see counters.h for more information
*/

#include <stdlib.h>
#include <stdio.h>
#include "counters.h"

/**************** local types ******************/
typedef struct counter { // Using static throws an error
    int key;
    int count;
    struct counter *next;
} counter_t;

/**************** global types *****************/
typedef struct counters {
    struct counter *head;
} counters_t;

/**************** local functions **************/
static counter_t *counter_new(int key)
{
    counter_t *counter = malloc(sizeof(counter_t));

    if (counter == NULL) {
        return NULL; // Error allocating memory
    } else {
        // Initialize contents
        counter->key = key;
        counter->count = 0;
        return counter;
    }
}

/**************** global functions **************/
counters_t *counters_new(void)
{
    counters_t *counters = malloc(sizeof(counters_t));

    if (counters == NULL) {
        return NULL; // Memory was not properly allocated
    } else {
        counters->head = NULL;
        return counters;
    }
}

void counters_add(counters_t *ctrs, const int key)
{
    // Make sure ctrs and key are valid
    if (ctrs != NULL && key >= 0) {
        // See if key already exists
        if (counters_get(ctrs, key) == 0) {
            counter_t *new = counter_new(key);
            new->count = 1;

            // Add it to the head of the list
            if (new != NULL) {
                new->next = ctrs->head;
                ctrs->head = new;
            }
        } else {
            counters_add(ctrs, key);
        }
    }
}

int counters_get(counters_t *ctrs, const int key)
{
    if (ctrs != NULL && key >= 0) {
        // Iterate to find the right key
        for (counter_t *counter = ctrs->head; counter != NULL;
            counter = counter->next) {

            if (counter->key == key) {
                return counter->count;
            }
         }
    }

    return 0; // If key wasn't found
}

void counters_set(counters_t *ctrs, const int key, int count)
{
    if (ctrs != NULL && key >= 0 && count >= 0) {
        // Iterate to find the right key
        for (counter_t *counter = ctrs->head; counter != NULL;
            counter = counter->next) {

            if (counter->key == key) {
                counter->count = count;
                return;
            }
        }
        // If function doesn't return, key wasn't found and we to make a new counter
        counters_add(ctrs, key);
        counters_set(ctrs, key, count);
    }
}

void counters_print(counters_t *ctrs, FILE *fp)
{
    if (fp != NULL) {
        if (ctrs != NULL) {
            fputc('{', fp);
            for (counter_t *counter = ctrs->head; counter != NULL;
                counter = counter->next) {
                // Print node
                fprintf(fp, "%d:%d", counter->key, counter->count);

                // Fixes comma at end of list
                if (counter->next != NULL) {
                    fputc(',', fp);
                }
            }
            fputc('}', fp);
            fputs("\n", fp);
        } else {
            fputs("(NULL)\n", fp);
        }
    }
}

void counters_iterate(counters_t *ctrs, void *arg,
    void (*itemfunc)(void *arg, const int key, int count))
{
    if (ctrs != NULL && itemfunc != NULL) {
        // Call itemfunc with arg on each item
        for (counter_t *counter = ctrs->head; counter != NULL;
            counter = counter->next) {
                (*itemfunc)(arg, counter->key, counter->count);
        }
    }
}

void counters_delete(counters_t *ctrs)
{
    if (ctrs != NULL) {
        for (counter_t *counter = ctrs->head; counter != NULL;) {
            counter_t *next = counter->next;
            free(counter);
            counter = next; // Iterate
        }
        free(ctrs);
    }
}
