#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

void start_writer();

int main(){
	struct timeval st , et;
	
    gettimeofday(&st , NULL);    
    start_writer();
    gettimeofday(&et , NULL);
    
	printf("Tempo total de execução do programa: %lu seconds\n",(et.tv_sec - st.tv_sec));
     
return 0;
}

void start_writer(){

	int i;
    pid_t pid;
    time_t t;
	int status;
	int vec_status[10];
	
    for(i=0;i<10;i++){
        pid=fork();

        if (pid==0){
			execl("./wchild", "wchild" , NULL);
			
		}else{
			vec_status[i]=status;
		}
       
	}
	
    for(i=0;i<10;i++)
		wait(& vec_status[i]);	
	
}
