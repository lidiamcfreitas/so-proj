#ifndef __WRITER_H__
#define __WRITER_H__

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* writer - opens a random file, gets a random string and writes it 
* 1024 times; repeats the process 5120 times */
int writer();

/* init - initializes vector strings */
char** init(char** strings);

/* random_file - changes filename to a random file name of 5 possible */
char* random_file(char* filename);

/* random_string - modifies buffer to a random string from vector strings */
char* random_string(char** strings, char* buffer);

/* open_write - opens random file and writes random string 1024 times */
void open_write(char* filename, char* buffer);

#endif
