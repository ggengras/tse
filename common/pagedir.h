/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* pagedir.h -
*
* See pagedir.h for full documentation
*/

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include "webpage.h"
#include "hashtable.h"

// * * * * * * * * Function Declarations * * * * //

/* Takes a file of the format saved by `savePage` (URL on the first line,
 * depth on the second line, HTML on the rest of the lines) and loads it
 * into a webpage structure.
 *
 */
webpage_t *loadPage(FILE *fp);

/* Takes a directory containing crawler output and loads the
 * data into a hashtable structure where each element is a
 * set containing (URL:webpage_t)
 *
 * Returns a pointer to dynamically allocated memory
 * containing the hashtable
 */
hashtable_t *loadPageDir(DIR *dp);

/* Saves a webpage structure to a file with the URL on the first line,
 * depth on the second line, and HTML on the rest of the lines.  The name of the
 * file is the integer ID number provided as an argument.
 *
 * Returns `true` if successful, else `false`.
 */
bool savePage(webpage_t *page, char *pageDirectory, int ID);

/* Takes a hashtable where each element is a
 * set containing (URL:webpage_t) and saves
 *
 *
 * Returns `true` if successful, else `false`
 */
bool savePageDir(hashtable_t *pages, DIR *dp);

#endif //__PAGEDIR_H
