#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char filename[14];
char buffer[11];
int file_descriptor;
int size_buffer = sizeof(buffer);

void open_random_file(){
    int i;
    i = rand() % 5; /*random number from 0 to 4 */
    char path[16];

    sprintf(filename, "SO2014-%d.txt", i);
    sprintf(path, "./%s", filename);

    file_descriptor = open(path, O_RDONLY);
}

void read_string(){
    read(file_descriptor, buffer, size_buffer);
}


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
}
