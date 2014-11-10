#include "common.h"

char* path;
int LOCK;

/*
 * main program
 */
 
int main(int argc, char *argv[]){
   
    int i;
    
    i=atoi(argv[1]);
    
    #if 0
    PRINTFs APENAS PARA DEBUG -------------------------
    #endif
    
    printf("%s\n", argv[1]);
    int res=reader(i);


    return res;
}



/* reader - saves first string and compares to the others. closes file */
int reader(char* h){

    /* variable initialization */
    char* buffer= (char*) malloc(sizeof(char)*11);
    char first_string[11];
    int i, file_descriptor;
    int size_buffer = sizeof(char)*11;

    /* opens random file */
    file_descriptor = open_file(h);

    if(LOCK == -1){ 
        printf("%s \n", strerror(errno));
        close(file_descriptor);		
    }else{   

        /* saves the first string from the opened file */
        buffer = read_string(file_descriptor,buffer,size_buffer);
        strcpy(first_string, buffer);

        for(i=1;i<1024;i++)
        {   /* reads next string */
            buffer = read_string(file_descriptor,buffer,size_buffer);

            /* reached end of file before it was supposed*/
            if (strcmp(buffer, "error") == 0) {
                printf("Erro de Acesso ao Ficheiro");
                free(buffer);
                LOCK=flock(file_descriptor, LOCK_UN);				
                close(file_descriptor);

                return -1;
            }
            else {
                /* string read is different from first string) */
                if(strcmp(first_string, buffer) != 0){
                    LOCK=flock(file_descriptor, LOCK_UN);
                    close(file_descriptor);
                    free(buffer);

                    return -1;
                }
            }

        }
        /* reads the 1025th line */
        buffer = read_string(file_descriptor,buffer,size_buffer);
        LOCK=flock(file_descriptor, LOCK_UN);
        close(file_descriptor);

        /* if the file has more than 1024 lines it is wrong */
        if (strcmp(buffer, "error") != 0){
            printf("%s", buffer);
            free(buffer);
            return -1;

        }
        /* exactly 1024 lines */
        else {
            free(buffer);
            return 0;
        }
    }
    return 0;
}



/* open_random_file - chooses random file, sets the path and opens it */
int open_file(int i){

    /* variable initialization */

    int file_descriptor, value;

    path = malloc (15);
    sprintf (path, "SO2014-%1d.txt", i);

    /* opens random file and returns it */
    file_descriptor = open(path, O_RDONLY);


    LOCK = flock(file_descriptor, LOCK_SH);


    return file_descriptor;
}



/* read_string - reads string from opened file */
char* read_string(int f_descriptor,char* buffer,int size){

    /* variable initialization */
    int result, bytes_read;
    char* error = "error";

    /* if bytes_read = 0: reached end of file and buffer should contain the message "error" */
    bytes_read = read(f_descriptor, buffer, size);
    if (bytes_read==0) {
        strcpy(buffer, error);
    }

    return buffer;

}

