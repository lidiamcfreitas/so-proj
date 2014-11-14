#ifndef __LEITOR_2_H__
#define __LEITOR_2_H__



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

/*-------------------------------------------------------------------------------------
| defines
+-------------------------------------------------------------------------------------*/

#define NB_THREADS 3
#define NB_FILES 5
#define NB_ENTRIES 1024
#define STRING_SZ 10

/*-------------------------------------------------------------------------------------
| Prototipos
+-------------------------------------------------------------------------------------*/

void * thread_code (void * args);
void init_myfiles ();


#endif