#include "reader.h"
#include <errno.h>

int LOCK;

/*
 * main program
 */
int main(){
	int res=reader();
    
	printf("%d\n",res);
    
	return 0;
}



/* reader - saves first string and compares to the others. closes file */
int reader(){
    
    /* variable initialization */
	char* buffer= (char*) malloc(sizeof(char)*11);
    char first_string[11];
	int i, file_descriptor;
	int size_buffer = sizeof(char)*11;
	
    /* opens random file */
    file_descriptor = open_random_file();
    
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
			
		
				close(file_descriptor);
				
				return -1;
			}
			else {
				/* string read is different from first string) */
				if(strcmp(first_string, buffer) != 0){
					close(file_descriptor);
					free(buffer);
					
					return -1;
				}
			}
			
		}
		/* reads the 1025th line */
		buffer = read_string(file_descriptor,buffer,size_buffer);
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
}


 
/* open_random_file - chooses random file, sets the path and opens it */
int open_random_file(){
    
    /* variable initialization */
	char path[15];
    int i,file_descriptor;
    
    /* initializes seed, needed for rand() to work properly */
	srand ( time(NULL) );
    i = rand() %5 ;
    sprintf(path, "./SO2014-%d.txt", i);
    
    /* opens random file and returns it */
    file_descriptor = open(path, O_RDONLY);
    
    printf("A LIDIZ DIZ SER ESTUPIDA ");
    
    printf("%s %i \n", path, file_descriptor);
    
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
 
