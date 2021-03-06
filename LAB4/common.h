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
void* reader(char** args);

/* open_random_file - chooses random file, sets the path and opens it */
int open_random_file();

/* read_string - reads string from opened file */
char* read_string(int f_descriptor,char* buffer,int size);

/* writer - opens a random file, gets a random string and writes it
 * 1024 times; repeats the process 5120 times */
int writer();

/* init - initializes vector strings */
char** init(char** strings);

/* random_file - changes path to a random file name of 5 possible */
char* random_file(char* path);

/* random_string - modifies buffer to a random string from vector strings */
char* random_string(char** strings, char* buffer);

/* open_write - opens a file and writes a string 1024 times */
void open_write(char* path, char* buffer);

#define NUM_CHILDREN 3

#endif
