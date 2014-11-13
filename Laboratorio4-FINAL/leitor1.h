#ifndef __COMMON_H__
#define __COMMON_H__

#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>


/* PROTOTYPES */

/* reader - saves first string and compares to the others. closes file */
int reader(int  h);

/* open_random_file - chooses random file, sets the path and opens it */
int open_file(int i);

/* read_string - reads string from opened file */
char* read_string(int f_descriptor, char* buffer, int size);
#define NUM_CHILDREN 3

#endif
