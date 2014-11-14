#ifndef __LEITOR_3_H__
#define __LEITOR_3_H__

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


#define L 1024
#define K 5
#define PORTION L/K

#define NB_FILES       5
#define NB_ENTRIES     1024
#define STRING_SZ      10

#define get_random(max) rand()%max


#endif