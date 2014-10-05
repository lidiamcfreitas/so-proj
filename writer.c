#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* variables initialization */
char strings[10][11];
char filename[14];
char buffer[11];

/* init - initializes vector strings */
void init(){
    int i,j;
    
    for(i=0; i<10; i++){
        for(j=0; j<9; j++){
            strings[i][j] = 'a'+ i ;
        }
        strings[i][j] = '\n';
        j++;
        strings[i][j] = '\0';
    }
}

/* random_file - changes filename to a random file name of 5 possible */
void random_file(){
    int i;
    i = rand() % 5; /*random number from 0 to 4 */
    
    sprintf(filename, "SO2014-%d.txt", i);
}

/* random_string - modifies buffer to a random string from vector strings */
void random_string(){
    int i;
    i = rand() % 10;
    
    strcpy(buffer, strings[i]);
}

/* open_write - opens random file and writes random string 1024 times */
void open_write(){
    int i, file_descriptor, size_buffer;
    size_buffer = sizeof(buffer);
    char path[16];

    /* OPEN FILE */
    /* mode - user has read permission, file owner has read, write and exec
    *         other have read permission */  
    mode_t mode = S_IRWXU | S_IRUSR | S_IROTH;
    sprintf(path, "./%s", filename);
    file_descriptor = open(path, O_CREAT|O_WRONLY|O_TRUNC , mode);
    
    /* WRITE FILE */
    for(i=0;i<1024;i++){
    write(file_descriptor, buffer, size_buffer);
    }

    close(file_descriptor);
}

int main(){
    int i;
    init();
    for(i=0;i<5120;i++){
        random_file();
    	random_string();
    	open_write();
    }   
    return 0;
}

