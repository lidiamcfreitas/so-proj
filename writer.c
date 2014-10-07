#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int writer();
char** init(char** strings);
char* random_file(char* filename);
char* random_string(char** strings, char* buffer);
void open_write(char* filename, char* buffer);




int main(){
    
    writer();
    return 0;
}



int writer(){
    int i;
    /* char strings[10][11]; */
    char **strings = malloc( 10 * sizeof(char *));
    for (i = 0; i < 11; i++){
            strings[i] = malloc(11 * sizeof(char));
    }
    
    /* char filename[15]; */
    char * filename = (char *) malloc(15*sizeof(char));
    
    /* char buffer[11]; */
    char * buffer = (char *) malloc(11*sizeof(char));
    
    strings = init(strings);
    for(i=0;i<5120;i++){
        filename = random_file(filename);
    	buffer = random_string(strings, buffer);
    	open_write(filename, buffer);
    }
    
    free(filename);
    free(buffer);
    
    for (i = 0; i < 10; i++){
        free(strings[i]);
    }
    
    free(strings);
    
    return 0;
}



/* init - initializes vector strings */
char** init(char** strings){
    int i,j;
    
    
    for(i=0; i<10; i++){
        for(j=0; j<9; j++){
            strings[i][j] = 'a'+ i ;
        }
        strings[i][j] = '\n';
        j++;
        strings[i][j] = '\0';
    }
    
    return strings;
}

/* random_file - changes filename to a random file name of 5 possible */
char* random_file(char* filename){
    int i;
    
    i = rand() % 5; /*random number from 0 to 4 */
    sprintf(filename, "./SO2014-%d.txt", i);
    
    return filename;
}

/* random_string - modifies buffer to a random string from vector strings */
char* random_string(char** strings, char* buffer){
    int i;
    i = rand() % 10;
    
    strcpy(buffer, strings[i]);
    
    return buffer;
}

/* open_write - opens random file and writes random string 1024 times */
void open_write(char* filename, char* buffer){
    int i, file_descriptor, size_buffer;
    size_buffer = sizeof(char)*11;  /* sizeof(buffer*) */

    /* OPEN FILE */
    /* mode - user has read permission, file owner has read, write and exec
    *         other have read permission */  
    mode_t mode = S_IRWXU | S_IRUSR | S_IROTH;
    
    file_descriptor = open(filename, O_CREAT|O_WRONLY|O_TRUNC , mode);
    
    /* WRITE FILE */
    for(i=0;i<1024;i++){
    write(file_descriptor, buffer, size_buffer);
    }

    close(file_descriptor);
}



