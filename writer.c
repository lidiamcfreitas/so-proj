#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include  <sys/types.h>

char vect[10][10];

void init(){
int i,j;

    for  (i=0;i<9;i++){
        for(j=0;j<9;j++)
             vect[i][j] = 'a' + i;        
        vect[i][9]= '\n';
     } 
}


FILE* fileopen(){

    char nomeficheiro[12];
	
    sprintf(nomeficheiro,"SO2014-%d.txt", rand() %5);

    FILE *fd = fopen(nomeficheiro, "a");
    if (fd == NULL)
           fd = fopen(nomeficheiro, "w+"); 
            
    return fd;
}

void escreve(){
    int i;
    FILE *fp=fileopen();               
    int cadeia2 = rand() % 10;	 

    fwrite(vect[cadeia2], sizeof(vect[0][0]), sizeof(vect[cadeia2]), fp);
    fclose(fp);
}

int main(){
	
	time_t t;
		
    int v;
    srand((unsigned) time(&t));

    init();
	
	
	pid_t  pid, pid2, pid3;
	int status, status1, status2; 
	
	int contaciclospai=0;
	int contaciclosfilho1=1;
	int contaciclosfilho2;
	int contaciclospai2;

	
    pid = fork();

    if (pid == 0){
    
        pid2 = fork();
        if(pid2 == 0){
            for(contaciclosfilho1=0;contaciclosfilho1<2560;contaciclosfilho1+=2){
                for(v=0;v<1024;v++)
                    escreve();                
            }
        }else{
            for(contaciclosfilho2=2560;contaciclosfilho2<5120;contaciclosfilho2+=2){

                for(v=0;v<1024;v++)
                    escreve();
            }
            wait(&status1);
        }
        
    }else{
    
        pid3 = fork();
        if(pid3 == 0){
            for(contaciclospai=1;contaciclospai<2560;contaciclospai+=2){
                for(v=0;v<1024;v++) 
                    escreve();
            }
        }else{
            for(contaciclospai2=2561;contaciclospai2<5120;contaciclospai2+=2){
                for(v=0;v<1024;v++)
                    escreve();                
            }
            wait(&status2);
        }
        wait(&status);
        
    }

    return 0;
    }
