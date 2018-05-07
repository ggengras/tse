# 'Tiny' Search Engine
## Graeme Gengras - Spring 2018

<<<<<<< HEAD
In the midst of development ...
=======
To get started::  

 * click the "Fork" button above; this should create a copy of this project in your Gitlab account. 
 * 	ensure that your new project is marked *PRIVATE*.
 * grant "Master" access to your new project to Professor and head grader.
 * if you have configured SSH access to Gitlab,
	 * copy the `git@gitlab` URL shown in the box in the middle of the screen;
 * otherwise, pick HTTPS instead of SSH above, and
	 * copy the `https` URL shown in the box in the middle of the screen.
 * In a Terminal window, log into `flume` or one of the other CS Unix hosts.
 * `cd cs50/labs`
 * `git clone URL`   # here, paste the URL you copied above
 * `cd tse`
 * edit `README.md` with your favorite editor
	 * replace these instructions with your name and a meaningful README like the one below. Then:
	 * `git add README.md ; git commit; git push`
 * start writing crawler in a subdirectory:
	 * `mkdir crawler`
	 * `echo crawler > crawler/.gitignore`
	 * edit `crawler/README.md`
	 * edit `crawler/Makefile`
	 * edit `crawler/crawler.c`

See [Lab 4 instructions](http://www.cs.dartmouth.edu/~cs50/Labs/Lab4)
for more information.

## A replacement README
Replace this README.md with the following, and add more information as needed.

```
# CS50 Tiny Search Engine

My Name - Summer 2017
>>>>>>> 719aa69e3c9518eceb438d8337472a0df52fda38

To build, run `make`.

To clean up, run `make clean`.

There is NO global `make test` yet, to test the crawler go to the crawler
directory and `make test`.

*Only* run the crawler on this domain to keep everyone happy:
`http://old-www.cs.dartmouth.edu/~cs50/data/tse`

NOTE::: Currently, makefile in libcs50 is configured to use the CS50 data structures
and not mine, but my .c files are in the libcs50 folder for when I get around to
fixing their memory leaks.
