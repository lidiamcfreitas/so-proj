/*-------------------------------------------------------------------------------------
| SO, Solução do Exercício 3, programa ESCRITOR
|
+-------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------
| includes
+-------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <sys/file.h> /* flock() */
#include <errno.h>

#include "exercicio1.h"
#include "exercicio2.h" /* consider NUM_CHILDREN */

#define NB_ITERATIONS    2000
#define NB_STRINGS         10


/*-------------------------------------------------------------------------------------
| fixed strings
+-------------------------------------------------------------------------------------*/

char mystrings[STRING_SZ][NB_STRINGS] = { "aaaaaaaaa\n", 
				"bbbbbbbbb\n",
				"ccccccccc\n",
				"ddddddddd\n",
				"eeeeeeeee\n",
				"fffffffff\n",
				"ggggggggg\n",
				"hhhhhhhhh\n",
				"iiiiiiiii\n",
				"jjjjjjjjj\n" };


char* myfiles[NB_FILES];


/*-------------------------------------------------------------------------------------
| init_myfiles
+-------------------------------------------------------------------------------------*/

void init_myfiles () {
  int i;

  for (i=0; i< NB_FILES; i++) {
    myfiles[i] = malloc (15);
    sprintf (myfiles[i], "SO2014-%1d.txt", i);
  }
}

/*-------------------------------------------------------------------------------------
| main
+-------------------------------------------------------------------------------------*/

int main (int argc, char** argv) {
  int   i;
  int contention=0;
  struct timeval tvstart; /* start time */

  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

  /* Initialize the seed of random number generator but use gettimeofday */
  if (gettimeofday(&tvstart, NULL) == -1) {
    perror("Could not get time of day, exiting.");
    exit(-1);
  }
  srandom ((unsigned)tvstart.tv_usec);
  //  srandom ((unsigned) time(NULL));

  init_myfiles ();

  /* Iterates NB_ITERATIONS/NUM_CHILDREN. Constant total number of writes */  
  for (i=0; i<NB_ITERATIONS/NUM_CHILDREN; i++) {
    char  *file_to_open = myfiles[get_random(NB_FILES)];
    int   fd  = open (file_to_open, O_RDWR | O_CREAT, mode);

    if (fd == -1) {
      perror ("Error opening file");
      exit (-1);
    }

    char *string_to_write  = mystrings[get_random(NB_STRINGS)];
    int  j;

    /* Measure the file locked rate. IT IS NOT MANDATORY */
    if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
      if (errno == EWOULDBLOCK)
	contention++;
      else {
	perror ("Error locking file");
	exit (-1);
      }
    }
/* Retries access, eventually blocking */
   if (flock(fd,LOCK_EX) < 0) {
      perror ("Error locking file");
      exit (-1);
    }

    for (j=0; j<NB_ENTRIES; j++) {
      if (write (fd, string_to_write, STRING_SZ) == -1) {
	perror ("Error writing file");
	exit (-1);
      }
    }


    if (flock(fd, LOCK_UN) < 0) {
      perror ("Error unlocking file");
      exit (-1);
    }

    if (close (fd) == -1)  {
      perror ("Error closing file");
      exit (-1);
    }
  }
  printf("%3d%% locked files. ", 100*contention/(NB_ITERATIONS/NUM_CHILDREN));
}
