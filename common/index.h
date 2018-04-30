/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* indexer.h -
*/

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>

// * * * * * * * * Global Types * * * * * * * * //
typedef struct index index_t;

// * * * * * * * * Function Declarations * * * * //

/* Takes an index file (written by saveIndex, or of the same
 * format) and loads it into an `index` data structure
 *
 * Returns a pointer to dynamically allocated memory
 * containing the index
 */
index_t *loadIndex(FILE *fp);

/* Takes an `index` data structure and writes
 * it to a file
 *
 * Returns `true` if successful, else `false`
 */
bool saveIndex(index_t *index, FILE *fp);

#endif //__INDEX_H
