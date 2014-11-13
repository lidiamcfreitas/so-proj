/*-------------------------------------------------------------------------------------
| SO, Solução do Exercício 3, programa ESCRITOR
|
|
+-------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------
| includes
+-------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include "exercicio2.h"


/*-------------------------------------------------------------------------------------
| main
+-------------------------------------------------------------------------------------*/

int main (int argc, char** argv) {

  pid_t pid;
  int runningChildren;

  //  time_t start, end; /* now use gettimeofday instead of time() */
  //  time(&start);

  struct timeval tvstart; /* start date */
  struct timeval tvend; /* end date */
  struct timeval tvduration; /* difference between both dates */
  unsigned int duration; /* difference between both dates in microseconds */

  time_t curtime; /* time in time_t format for format conversion */
  char buffer[30]; /* to write the date in a readable format */

  if (gettimeofday(&tvstart, NULL) == -1) {
    perror("Could not get time of day, exiting.");
    exit(-1);
  }
  curtime = tvstart.tv_sec;
  strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
  printf("Start: %s%ld\n",buffer,tvstart.tv_usec);
  
  for (runningChildren = 0; runningChildren < NUM_CHILDREN; runningChildren++) {
    
    pid = fork();
    if (pid < 0) {
      perror("Could not fork a child.");
      exit(-1);
    } else if (pid == 0) {

      if (execl("exercicio3-escritor", "exercicio3-escritor", NULL) == -1) {
	perror("Could not execute child program.");
	exit(-1);
      }

      printf("it should not reach this point...\n");
    }
  }
  
  int status, valorExit;

  printf("Parent will now wait for the children to exit.\n");

  while (runningChildren > 0) {
    pid = wait(&status);
    
    if (pid == -1) {
      perror("Error on wait.");
      exit(-1);
    }
    /* See SO FAQs for wait() handling */
    if (WIFEXITED(status)) {
      valorExit = (char) WEXITSTATUS(status);
      printf("Child with pid=%ld completed with status %d\n", (long)pid, valorExit);
    }
    else /* caso em que filho terminou sem exit ou return */
    printf("Child with pid=%ld completed without exit/return\n", (long)pid); 

    runningChildren --;
  }

  //  time(&end); /* remember: use gettimeofday instead of time() */
  //  double dif = difftime (end,start);
  //  printf ("Your calculations took %.2lf seconds to run.\n", dif );

  if (gettimeofday(&tvend, NULL) == -1) {
    perror("Could not get time of day, exiting.");
    exit(-1);
  }

  curtime=tvend.tv_sec;
  strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));

  printf("End: %s%ld\n",buffer,tvend.tv_usec);

  tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
  tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
  duration = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
  printf("Duration: %f seconds\n", (float)duration/1000000);
  return 0;
  
}
