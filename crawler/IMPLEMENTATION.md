# crawler.c Implementation
## Graeme Gengras, April 2018

### Algorithm
The crawler follows the basic logic detailed below:

1. execute from a command line

2. parse the command line, validate parameters, initialize other modules

3. make a webpage for the seedURL, marked with depth=0

4. add that page to the bag of webpages to crawl

5. add that URL to the hashtable of URLs seen

6. while there are more webpages to crawl,
    1. extract a webpage (URL,depth) item from the bag of webpages to be crawled,

    2. pause for at least one second,

    3. retrieve a webpage for that URL,

    4. write the webpage to the pageDirectory with a unique document ID

    5. if the webpage depth is < maxDepth, explore the webpage to find links:

        1. parse the webpage to extract all its embedded URLs;

        2. for each extracted URL,

            1. ‘normalize’ the URL

            2. if that URL is not ‘internal’, ignore it;

            3. try to insert that URL into the hashtable of URLs seen

                1. if it was already in the table, do nothing;

                2. if it was added to the table,

                1. make a new webpage for that URL, at depth+1

                2. add the new webpage to the bag of webpages to be crawled

### Function Structure
`crawler.c` has a relatively simple flow from function to function. There are
only three functions in the program: `main`, `crawler`, and `pageSaver`. `main`
simply contains code that parses the command line arguments, `crawler`
does everything after step 3 in the algorithm above, and `pageSaver` is a
utility function that writes a webpage to a file in the desired format.

### Included Modules
`crawler.c` utilizes data structures that I created, `bag` and `hashtable` (which
also uses `set`).  In addition, functionality for interfacing with the web is drawn
from `webpage.[ch]` provided by the cs50 faculty. 
