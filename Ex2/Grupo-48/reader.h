#ifndef __READER_H__
#define __READER_H__

/*
* list.h - definitions and declarations of the integer list 
*/

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* PROTOTYPES */

/* reader - saves first string and compares to the others. closes file */
int reader();

/* open_random_file - chooses random file, sets the path and opens it */
int open_random_file();

/* read_string - reads string from opened file */
char* read_string(int f_descriptor,char* buffer,int size);

#endif
