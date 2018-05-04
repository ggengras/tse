/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* glib.c -
*
* See glib.h for full documentation
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

char *strCat(char *str1, char *str2) {
    char *newString = calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));

    // Make sure calloc worked
    assert(newString != NULL);

    //// Populate newString
    strcpy(newString, str1);
    strcat(newString, str2);
    //strcpy(newString + strlen(str1), str2);

    //// Null terminate newString
    //newString[strlen(str1) + strlen(str2) + 1] = '\0';
    printf("%s\n", newString);

    return newString;
}
