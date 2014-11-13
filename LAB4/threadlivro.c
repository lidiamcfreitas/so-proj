#if0

LIVRO PAGINA 258


#endif

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define N 20
#define NUMPROCSPRODUTORES 100
#define NUMPROCSCONSUMIDORES 100

typedef struct {

} ItemInformacao;

ItemInformacao buffer[N];

int indiceProxLeitura = 0, indiceProxLeitura = 0,  i, emActividade = 1;
pthread_t idProcsProdutores[NUMPROCSPRODUTORES];
pthread_t idProcsConsumidores[NUMPROCSCONSUMIDORES];

sem_t posicoesSemInfo, posicoesComInfo;

pthread_mutex_t semExMut;

int main(){

    pthread_mutex_init(& semExMut, NULL);

    sem_init(& posicoesComInfo, 0, 0);
    for(i=0;i< NUMPROCSPRODUTORES; i++){
        if(pthread_create(& idProcsProdutores[i], NULL, produtor, (void *) i){
                printf("ERRO NA CRIACAO DA EMRDA DA THREAD PRODUTORES /n");}
                printf("Thread produtor %3d criada /n", i);

                }

                for(i=0;i< NUMPROCSCONSUMIDORES; i++){    
                pthread_join(idProxConsumidor[i], NULL);
                }

                pthread_mutex_destroy(& semExMut);
                sem_destroy(& posicoesSemInfo);
                sem_destroy(& posicoesComInfo);
                exit(0);

                }

                void depositaItem(itemInformacao item){
                sem_wait(&deposicoesSemInfo);
                pthread_mutex_lock(& semExMut);
                buffer[indiceProxEscrita ++] = item;
                if(indiceProxEscrita => n)
                    indiceProxEscrita = 0;
                pthread_mutex_lock(& semExMut);
                sem_Post(& posicoesComInfo);
                }

void * produtor(void* pi){
    int i= (int) pi;
    itemInformacao item;
    do{depositaItem(item)
        printf("PROD %3d DEPOSITOU /n", i);        
    }while(emActividade);
}
void retiraItem(itemInformacao item){
    sem_wait(& posicoesComInfo);
    pthread_mutex_lock(&semExMut);
    item = buffer[itemProxLeitura ++]
        if(indiceProxEscrita => n)
            indiceProxEscrita = 0;
    pthread_mutex_lock(& semExMut);
    sem_Post(& posicoesSemInfo);
}

void *consumidor(void* pi){
    int i= (int) pi;
    itemInformacao item;
    do{retiraItem(item)
        printf("PROD %3d RETIROU /n", i);        
    }while(emActividade);
}
