/*-------------------------------------------------------------------------------------
| SO, Solução do Exercício 3, programa LEITOR
|
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
#include <pthread.h>

//#include "exercicio1.h"
#define NB_THREADS 3
#define NB_FILES 5
#define NB_ENTRIES 1024
#define STRING_SZ 10

/*-------------------------------------------------------------------------------------
| fixed strings
+-------------------------------------------------------------------------------------*/
void * thread_code (void * args);

char* myfiles[NB_FILES];


/*-------------------------------------------------------------------------------------
| init_myfiles
+-------------------------------------------------------------------------------------*/


void init_myfiles () {
  int i,n,counter;
  int numbers[NB_FILES];
  char* tmp;
  srand(time(NULL));

  counter= NB_FILES;
  for (i=0; i< NB_FILES; i++) {
    myfiles[i] = malloc (15);
    sprintf (myfiles[i], "SO2014-%1d.txt", i);
  }
  
  for(i=0;i< NB_THREADS;++i){
    n = rand() % counter;
    tmp = myfiles[n+i];
    myfiles[n+i] = myfiles[i];
    myfiles[i] = tmp;
    counter--;

  }
}

int main(){
	struct timeval st , et;
	int i, error;
	pthread_t threads[NB_THREADS];
	int returnValues[NB_THREADS];

	init_myfiles ();
	gettimeofday(&st , NULL);

	for(i=0;i<NB_THREADS;i++){
		
		error = pthread_create(&threads[i], NULL, thread_code, (void *)myfiles[i]);
		
	}

	for(i=0;i<NB_THREADS;i++){
		pthread_join(threads[i], (void *) &returnValues[i]);
		if (returnValues[i] == 1){
			printf("It's ok!!!\n");
		} else {
			printf("It's wrong\n");
		}
	}	

	gettimeofday(&et , NULL);
   	printf("Running time of program: %d microseconds\n",(et.tv_usec - st.tv_usec));
	
	return 0;
}


/*-------------------------------------------------------------------------------------
| thread_code
+-------------------------------------------------------------------------------------*/

void * thread_code (void * args) {
  char* file_to_open = malloc(15);
 // sprintf(file_to_open, (char *) args);
 file_to_open = (char*)args;
	printf("%s\n", file_to_open);
  int   fd;
  struct timeval tvstart; /* start time */

  

  /* Initialize the seed of random number generator but use gettimeofday */
  if (gettimeofday(&tvstart, NULL) == -1) {
    perror("Could not get time of day, exiting.");
    pthread_exit((void*)-1);
  }
  srandom ((unsigned)tvstart.tv_usec);
  //  srandom ((unsigned) time(NULL));


  fd  = open (file_to_open, O_RDONLY);

  printf("Monitor will check if file %s is consistent...\n", file_to_open);

  if (fd == -1) {
    perror ("Error opening file");
    pthread_exit ((void*)-1);
  }
  else {
    char string_to_read[STRING_SZ];
    char first_string[STRING_SZ];
    int  i, nbytes;

/* Shared lock - Blocking
    if (flock(fd, LOCK_SH) < 0) {
      perror ("Error locking file");
      exit (-1);
    }
*/

/* Shared lock - Non blocking */
    if (flock(fd, LOCK_SH | LOCK_NB) < 0) {
      if (errno == EWOULDBLOCK)
		perror ("Wait unlock");
      else {
		perror ("Error locking file");
		pthread_exit ((void*)-1);
      }
    }
    /* Retry lock, this time blocking */
    if (flock(fd, LOCK_SH) < 0) {
      perror ("Error locking file");
      pthread_exit ((void*)-1);
    }

    if (read (fd, first_string, STRING_SZ) == -1) {
      perror ("Error reading file");
      pthread_exit ((void*)-1);
    }
    for (i=0; i<NB_ENTRIES-1; i++) {
      
      if ((nbytes = read (fd, string_to_read, STRING_SZ)) == -1) {
		perror ("Error reading file");
		pthread_exit ((void*)-1);
      }
      if (nbytes == 0){
		fprintf (stderr, "\nInconsistent file (too few lines): %s\n", file_to_open);
		pthread_exit ((void*)-1);
      }

      if (strncmp(string_to_read, first_string, STRING_SZ)) {
		fprintf (stderr, "\nInconsistent file: %s\n", file_to_open);
		pthread_exit ((void*)-1);
      }
    }
    
    if (read (fd, string_to_read, STRING_SZ) > 0){
		fprintf (stderr, "\nInconsistent file (too many lines): %s\n", file_to_open);
		pthread_exit ((void*)-1);
    }
    
    /*Falta teste para ver se existem mais do que 1024 linhas*/
 
    if (flock(fd, LOCK_UN) < 0) {
      perror ("Error unlocking file");
      pthread_exit ((void*)-1);
    }

    if (close (fd) == -1)  {
      perror ("Error closing file");
      pthread_exit ((void*)-1);
    }
  }
  pthread_exit((void*)1);
}
