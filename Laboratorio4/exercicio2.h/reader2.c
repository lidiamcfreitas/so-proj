#include "common_reader2.h"
#include <pthread.h>

char* path;
int LOCK;
int finish;
/*
 * main program
 podes criar threads como jolinable ou detachabel 
 se for em detachec qnd elas fizerem exit vao limpar tdos os seus recursos enquando sque se forme joinable tem que haver uma thread como o memso process id que faca join para libertar recussos que  e o problema que estou a ter 
 */

#define NUMTHREADS 3
#define FILENUMBER 5


/* reader - saves first string and compares to the others. closes file */

void* reader(void* args){
    printf("1\n");
    char *filename;
    /* variable initialization */
    char* buffer= (char*) malloc(sizeof(char)*11);
    char first_string[11];
    int i, file_descriptor;
    int size_buffer = 11 * sizeof(char);
    
	filename = (char*) malloc(sizeof(char) * 13);
	sprintf(filename,(char*) args);

    /* open file */

	 
    printf("filename : %s \n ", filename);
    file_descriptor = open_file(filename);
    printf("tudo ok 1.1\n");

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
                printf("insucesso 1\n");
                finish++;
#if 0
                return -1;

#endif
                pthread_exit(  (int*) -1) ;


            }
            else {

                /* string read is different from first string) */
                if(strcmp(first_string, buffer) != 0){
                    LOCK=flock(file_descriptor, LOCK_UN);
                    close(file_descriptor);
                    free(buffer);
                    printf("insucesso 2\n");
                    finish++;
                    pthread_exit( (int*) -1);
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
            printf("insucesso 3\n");
            finish++;
            pthread_exit( (int*) -1);
        }
        /* exactly 1024 lines */
        else {
            free(buffer);
            printf("sucesso1\n");
            finish++;
            pthread_exit( (int*) 0);
        }
    }
    pthread_exit( (int*) 0);
}


/* open_file - Open file specified by LEITOR-PAI-2 */
int open_file(char path[13]){

    /* variable initialization */

    int file_descriptor, value;
    /* opens file and returns it */
    file_descriptor = open(path, O_RDONLY);
    if (file_descriptor == -1){
		 	perror ("Error opening file");
      	exit (-1);
      	}
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

int main(int argc, char *argv[]){
    finish=0;
    pthread_t *t_id=(pthread_t*)malloc(3*sizeof(pthread_t));
    char* filename;    
    pthread_t* thread_id;
    int i,n,tmp;
    int* exitValue; 
    int randomnumbers[NUMTHREADS];
    int numbers[5];
    pthread_attr_t *attr;
    int finished;
    struct timeval st , et;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    thread_id = (pthread_t*) malloc(NUMTHREADS*sizeof(pthread_t));

    
	filename = (char**) malloc(sizeof(char*) * FILENUMBER) ;

    srand(time(NULL));
    
 // Initialize the array
	for(i = 0;i < FILENUMBER;++i){
   	numbers[i] = i;
	}
 
  // Shuffle the array
  for(i = 0;i < FILENUMBER;++i){
    n = rand() % FILENUMBER;
    tmp = numbers[n];
    numbers[n] = numbers[i];
    numbers[i] = tmp;

	 filename[i]=malloc(15);
    sprintf(filename[i], "SO2014-%1d.txt",numbers[i]);    
    printf("%s",filename[i]);
  }
 
    gettimeofday(&st , NULL);

    printf("tudo ok 0\n");

    for(i=0;i<NUMTHREADS;i++){
                
        if(pthread_create(&thread_id[i], NULL , reader,(void*) filename[i]) != 0){
            printf("Failed to Create thread");
        }


        printf("%s", filename);
    }
    
    printf("tudo ok 1\n");

    while(finish !=  NUMTHREADS ){
        sleep(0.0001);
    }

   // while(finished < NUMTHREADS){
     //   for(i=0;i<NUMTHREADS;i++){
            // if(pthread_join(thread_id[i],(void *) &exitValue) == NULL){
            //    printf("Fail to join the thread %d\n", i);
            // }else{
            //    finished++ ;

            //	}

           // pthread_join(thread_id[i],NULL);

       // }
   // }


    printf("tudo ok 2\n");
    gettimeofday(&et , NULL);

    printf("Tempo total de execução do programa: %lu seconds\n",(et.tv_sec - st.tv_sec));
    pthread_attr_destroy(&attr);
    return 0;
}


