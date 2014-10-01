#include <unistd.h>
#include <sys/types.h>

char vect[10][10];
char nomeficheiro;
char buffer[11];

void init(){
int i,j;

    for  (i=0;i<9;i++){
        for(j=0;j<9;j++)
             vect[i][j] = 'a' + i;        
        vect[i][9]= '\n';
     } 
}

char randomfile(){
	
	    sprintf(nomeficheiro,"SO2014-%d.txt", rand() %5);
	    
	return nomeficheiro;
}

char* randomstring(){
		    int cadeia2 = rand() % 10;
		    buffer=vect[cadeia2];
		    
		    return buffer;
}


int main(){
		
    int u,v;
	char filename, string;
   
	
	for(v=0;v<5121;v++){
			for(u=0;u<1025;u++){	
				init();
				filename=randomfile();
				string=randomstring();
				open(filename,w+);
				ssize_t write(filename, buffer, sizeof(buffer));
				close(filename);
			}
	}

    return 0;
    }
