/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* indexer.c -
*/

#include <stdio.h>
#include "index.h"
#include "pagedir.h"
#include "glib.h"

// * * * * * * * * Function Declarations * * * * * * * * //
//          See implementation section for details       //

int main(int argc, char *argv[])
{
    // Parse the command line, validate parameters
    // Check for # of args
    if (argc != 3) {
        fprintf(stderr, "Usage: ./indexer pageDirectory indexFilename\n");
        exit(1);
    }

    // Check for presence of `.crawler` file in `pageDirectory`
    char *pageDirectory = argv[1];
    char *dirTest = "/.crawler";
    char *filename = strCat(pageDirectory, dirTest); // strCat allocs memory

    if (filename == NULL) { // Make sure alloc worked properly
        fprintf(stderr, "Error: Failed to allocate filename for ./crawler\n");
        exit(10);
    }

    FILE *fp;
    if ( (fp = fopen(filename, "r")) == NULL ) {
        fprintf(stderr,
            "Error: Specified directory does not contain valid crawler output\n");
        exit(2);
    }
    // Clean up
    free(filename); // From strCat
    fclose(fp);

    // Create `indexFilename`, overwrite if it exists
    if ( (fp = fopen(argv[2], "w")) == NULL ) {
        fprintf(stderr,
            "Error: Cannot open %s\n", argv[2]);
        exit(3);
    }



}
