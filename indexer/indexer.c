/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* indexer.c -
*/

#include "index.h"
#include "pagedir.h"

// * * * * * * * * Function Declarations * * * * * * * * //
//          See implementation section for details       //

int main(int argc, char *argv[]) {
    // Parse the command line, validate parameters
    // Check for # of args
    if (argc != 3) {
        fprintf(stderr, "./indexer pageDirectory indexFilename\n");
        exit(1);
    }





    // Check for presence of `.crawler` file in `pageDirectory`
    char *dirTest = ".crawler";
    char *filename = calloc(strlen(argv[1]) + strlen(dirTest) + 2,
        sizeof(char));

    if (filename == NULL) { // Make sure alloc worked properly
        fprintf(stderr, "Failed to allocate filename for ./crawler\n");
        exit(10);
    }

    // Populate filename
    strcpy(filename, pageDirectory);
    strcpy(filename + strlen(pageDirectory), "/");
    strcpy(filename + strlen(pageDirectory) + 1, dirTest);

    // Null terminate filename string
    filename[strlen(pageDirectory) + strlen(dirTest) + 1] = '\0';

}
