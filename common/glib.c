/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* glib.c -
*
* See glib.h for full documentation
*/

#include <string.h>
#include <stdlib.h>

char *strCat(char *str1, char *str2) {
    char *newString = calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));

    // Populate newString
    strcpy(newString, str1);
    strcpy(newString + strlen(str1), str2);

    // Null terminate newString
    newString[strlen(str1) + strlen(str2) + 1] = '\0';

    return newString;
}
