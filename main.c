#include "time.h"
#include <stdio.h>
#include <unistd.h>

void funcao();

clock_t t;

int main(){
	double elapsed;
	clock_t t;
	int function_time;
	
    t = clock();
    
    funcao();
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
    printf("fun() took %f seconds to execute \n", time_taken);

return 0;
}

void funcao(){

	int i;
    pid_t pid;
    time_t t;
	int status;
	int vec_status[10];
	
    for(i=0;i<10;i++){
        pid=fork();

        if (pid==0){
			execl("./writer", "writer" , NULL);
			
		}else{
			vec_status[i]=status;
		}
       
	}
	
    for(i=0;i<10;i++)
		wait(& vec_status[i]);	
	
}
