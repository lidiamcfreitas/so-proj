#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* variables initialization */
char filename[14];
char buffer[11];
int file_descriptor;
int size_buffer = sizeof(buffer);

/* open_random_file - chooses random file, sets the path and opens it */
void open_random_file(){
    int i;
    i = rand() % 5; /*random number from 0 to 4 */
    char path[16];

    sprintf(filename, "SO2014-%d.txt", i);
    sprintf(path, "./%s", filename);

    file_descriptor = open(path, O_RDONLY);
}

/* reads string from opened file */
void read_string(){
    read(file_descriptor, buffer, size_buffer);
}

/* saves first string and compares to the others. closes file */
int main(){
    char first_string[11];
    int i,j=0;
    size_buffer = sizeof(buffer);

    open_random_file();
    read_string();
    strcpy(first_string, buffer);
    for(i=1;i<1024;i++)
    {   
    	read_string();
        if(strcmp(first_string, buffer) != 0){
            j=-1;
        }
    }
    printf("%d",j);
    close(file_descriptor);
}
