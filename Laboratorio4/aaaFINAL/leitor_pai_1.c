#include "leitor1.h"

void start_reader();

int main(int argc, char *argv[]){
    struct timeval st , et;

    gettimeofday(&st , NULL);    
    start_reader();
    gettimeofday(&et , NULL);

    printf("Tempo total de execução do programa: %lu seconds\n",(et.tv_sec - st.tv_sec));

    return 0;
}

void start_reader(){

    int i,r;
    pid_t pid;
    time_t t;
    int status, valorExit, runningChildren;
    int vec_status[3];
    char u[2];

    int j;
 

    srand( time(NULL));

    for (runningChildren = 0; runningChildren < NUM_CHILDREN; runningChildren++) {
        j = rand() %5;
        sprintf(u, "%d", j); 
        pid = fork();

        if (pid < 0) {
            perror("Could not fork a child.");
            exit(-1);
        } else if (pid == 0) {



            if (execl("reader1","leitor_filho_1",u,NULL) == -1) {
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
