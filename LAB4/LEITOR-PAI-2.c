#include "common.h"

//DEFINE K EM H / ATOI() / LSEEK() / NOTAS DADAS PELO PROF NA TEORICA

void start_reader();

typedef struct thread_info {    /* Used as argument to thread_start() */
           pthread_t thread_id;        /* ID returned by pthread_create() */
           int       thread_num;       /* Application-defined thread # */
           char     *argv_string;      /* From command-line argument */
}THREAD_INFO;

int main(int argc, char *argv[]){
    struct timeval st , et;
    
    pthread thread_a, thread_b, thread_c;
    
    j = rand() %5;
    
    gettimeofday(&st , NULL);
    
    int threada = pthread_create(&thread_a, NULL, start_reader, filename);
    int threadb = pthread_create(&thread_b, NULL, start_reader, filename);
    int threadc = pthread_create(&thread_c, NULL, start_reader, filename);  
      
    gettimeofday(&et , NULL);

    printf("Tempo total de execução do programa: %lu seconds\n",(et.tv_sec - st.tv_sec));

    return 0;
}

void * start_reader(void * data){

    int i,r;
    pid_t pid;
    time_t t;
    int status, valorExit, runningChildren;
    int vec_status[3];
    char u[2];

    int j;

    sprintf(u, "%d", j);    

    srand( time(NULL));

    for (runningChildren = 0; runningChildren < NUM_CHILDREN; runningChildren++) {
        j = rand() %5;
        sprintf(u, "%d", j); 
        
        pid = fork();

        if (pid < 0) {
            perror("Could not fork a child.");
            exit(-1);
        } else if (pid == 0) {
            if (execl("reader1","reader1",u,NULL) == -1) {
                perror("Could not execute child program.");
                exit(-1);
            }
        }
    }

    while (runningChildren > 0) {

        if (wait (&status) == -1) { printf("Wait Failed"); }

        if (WIFEXITED(status)) {
            valorExit = (char) WEXITSTATUS(status);
            printf("Filho terminou e devolveu %d\n", valorExit);
        }
        else{
            printf("Child with pid=%ld completed without exit/return\n", (long)pid); 
        }
        runningChildren --;
    }
}


void* work(void *thread_data){


