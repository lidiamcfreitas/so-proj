#include "time.h"
#include <stdio.h>
#include <unistd.h>

int main(){
    int i;
    pid_t pid;
    time_t t;

    for(i=0;i<10;i++){
        printf("antes do fork\n");
        pid=fork();

        if (pid==0)
			execl("./writer", "writer" , NULL);
    }
    
    //printf ("%d\n", sizeof(time_t));
    
    return 0;
}
