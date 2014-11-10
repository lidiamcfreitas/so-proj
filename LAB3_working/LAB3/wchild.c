#include "wchild.h"
#include <sys/file.h>
#include <errno.h>
#include <sys/stat.h>

/*
 * main program
 */
int main(){

    /* initializes seed, needed for rand() to work properly */
    srand ( time(NULL) );

    writer();

    return 0;
}



/* writer - opens a random file, gets a random string and writes it
 * 1024 times; repeats the process 5120 times */
int writer(){

    /* variables initialization */
    int i;
    char **strings = malloc( 10 * sizeof(char *));
    char * path = (char *) malloc(15*sizeof(char));
    char * buffer = (char *) malloc(11*sizeof(char));
    for (i = 0; i < 10; i++){
        strings[i] = malloc(11 * sizeof(char));
    }

    strings = init(strings);
    for(i=0;i<512;i++){

        /* opens random file, and writes random string 1024 times */
        path = random_file(path);
        buffer = random_string(strings, buffer);
        open_write(path, buffer);
    }

    free(path);
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


/* random_file - changes path to a random file name of 5 possible */
char* random_file(char* path){
    int i;

    i = rand() % 5;
    sprintf(path, "./SO2014-%d.txt", i);

    return path;
}


/* random_string - modifies buffer to a random string from vector strings */
char* random_string(char** strings, char* buffer){
    int i;
    i = rand() % 10;

    strcpy(buffer, strings[i]);

    return buffer;
}


/* open_write - opens a file and writes a string 1024 times */
void open_write(char* path, char* buffer){
    int i, file_descriptor, size_buffer, LOCK;
    mode_t mode = S_IRWXU | S_IRUSR | S_IROTH;
    size_buffer = sizeof(char)*11;

    /* mode - user has read permission, file owner has read, write and exec
     *         others have read permission */

    file_descriptor = open(path, O_CREAT|O_WRONLY , mode);

    LOCK = flock(file_descriptor, LOCK_EX);

    if(LOCK == 0){	

        for(i=0;i<1024;i++){

            write(file_descriptor, buffer, size_buffer);

        }
    }else{
        printf("%s \n", strerror(errno));
    }

    close(file_descriptor);

    LOCK = flock(file_descriptor, LOCK_UN);
}
