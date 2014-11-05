#include "common.h"

//DEFINE K EM H / ATOI() / LSEEK() / NOTAS DADAS PELO PROF NA TEORICA

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
    int status;
    int vec_status[3];
    char *u;

    srand( time(NULL));
    
    for(i=0;i<3;i++){
        r = rand() % 5; 

            printf("Im darth vader\n");
        
             
        pid=fork();
        

            
        if (pid==0){
            printf("Im a luke.\n");
            
            sprintf(u, "%d", r);            
            execl("reader1","reader1",u,NULL);
            printf("execl failed");
            
        }else if (pid==-1){
            printf("failed to fork");

        }else{
            vec_status[i]=status;
        }

    }

    for(i=0;i<3;i++)
        wait(& vec_status[i]);	

}

