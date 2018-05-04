/* 'Tiny' Search Engine
*  Graeme Gengras, April 2018
*
* indexertest.c -
*/

#include "index.h"
#include "pagedir.h"

int main(int argc, char *argv[]) {
    // Parse the command line, validate parameters
    // Check for # of args
    if (argc != 3) {
        fprintf(stderr, "Usage: ./indextest oldIndexFilename newIndexFilename\n");
        exit(1);
    }

    FILE *loadFile;
    if ( (loadFile = fopen(argv[1], "r")) == NULL ) {
        fprintf(stderr,
            "Error: Cannot open %s\n", argv[1]);
        exit(2);
    }

    // Create & load index
    index_t *index = indexNew(500);
    indexLoad(index, loadFile);
    fclose(loadFile);

    // Create `newIndexFilename`, overwrite if it exists
    FILE *saveFile;
    if ( (saveFile = fopen(argv[2], "w")) == NULL ) {
        fprintf(stderr,
            "Error: Cannot open %s\n", argv[2]);
        exit(3);
    }

    // Save index and clean up
    indexSave(index, saveFile);
    indexDelete(index);
    fclose(saveFile);
}
