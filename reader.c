//#include <unistd.h>
//#include <sys/types.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//
///* mover para o header file */
//int reader();
//int open_random_file();
//char* read_string(int f_descriptor,char* buffer,int size);

#include "reader.h"

int main(){
	int res=reader();
	printf("%d\n",res);
	return 0;
}

/* reader - saves first string and compares to the others. closes file */
int reader(){
	char* buffer= (char*) malloc(sizeof(char)*11);
    char first_string[11];
	int i,file_descriptor;
	int size_buffer = sizeof(char)*11; /* int size_buffer = sizeof(buffer*); */
	
    file_descriptor = open_random_file();
    buffer = read_string(file_descriptor,buffer,size_buffer);
    strcpy(first_string, buffer);
    for(i=1;i<1024;i++)
	{   
        buffer = read_string(file_descriptor,buffer,size_buffer);
        if (strcmp(buffer, "error") != 0) { /* nao chegou ao final do ficheiro */
            if(strcmp(first_string, buffer) != 0){ /* strings nao sao iguais) */
                close(file_descriptor);
                free(buffer);
                return -1;
			}
        }
        else{ /* chegou ao final do ficheiro */
            close(file_descriptor);
            /* free(buffer); */
            return -1;
        }
		
    }
    close(file_descriptor);
	free(buffer);
	return 0;
}
 
/* open_random_file - chooses random file, sets the path and opens it */
int open_random_file(){
	char path[15];
	
    int i,file_descriptor;
	srand ( time(NULL) ); /* initialize seed */
    i = rand() %5 ; /*random number from 0 to 4 */
    sprintf(path, "./SO2014-%d.txt", i);
    file_descriptor = open(path, O_RDONLY);
	return file_descriptor;
}
 
/* read_string - reads string from opened file */
char* read_string(int f_descriptor,char* buffer,int size){
	int result, bytes_read;
    char* error = "error";
    
    bytes_read = read(f_descriptor, buffer, size);
    if (bytes_read==0) {
        strcpy(buffer, error);
    }
    return buffer;

}
 
