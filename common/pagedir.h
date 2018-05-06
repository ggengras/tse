/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* pagedir.h - A collection of functions for manipulating 'crawler' directories
*/

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include "webpage.h"
#include "hashtable.h"

// * * * * * * * * Function Declarations * * * * //

/* Saves a webpage structure to a file with the URL on the first line,
 * depth on the second line, and HTML on the rest of the lines.  The name of the
 * file is the integer ID number provided as an argument.
 *
 * Returns `true` if successful, else `false`.
 */
bool savePage(webpage_t *page, char *pageDirectory, int ID);

#endif //__PAGEDIR_H
