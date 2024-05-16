#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NT 4
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef struct{
    int size;
    int *v;
    int media;
}Th;

int* creavettore(int n){
    int* v = (int*) malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        v[i] = rand() % 255;
    }
    return v;
}

void leggivettore(int n, int *v){
    for(int i = 0; i < n; i++)
        printf("[%d]", v[i]);
    printf("\n");
}

void* valorimedi(void* arg){
    Th* th = (Th*)arg;
    int somma = 0, media = 0;
    for(int i = 0; i < th->size; i++){
        pthread_mutex_lock(&mutex);
        somma += th->v[i];
        pthread_mutex_unlock(&mutex);
    }
    th->media = somma/th->size;
    
}

int main(int argc, char *argv[]){
    int n = 0;
    if(argc < 2){
        printf("Inserire un argomento un numero >= 24 che sia anche un multiplo di 4\n");
        return 1;
    }
    
    n = atoi(argv[1]);

    if(n < 24){
        printf("Inserire un numero da 24 in poi\n");
        return 1;
    }
    else if(n % 4 != 0){
        printf("il numero non è un multiplo di 24 \n");
        return 1;
    }

    int *v = creavettore(n);
    leggivettore(n,v);

    pthread_t thread[NT];
    Th th[NT];

    for(int i=0; i<NT; i++){
        th[i].size  = n / NT;
        th[i].media = 0;
        th[i].v     = &v[i * (th[i].size)];
        pthread_create(&thread[i], NULL, valorimedi, (void*)&th[i]);
    }

    for(int i = 0; i < NT; i++){
        pthread_join(thread[i], NULL);
        printf("Thread[%d], la media della porzione di array calcolata è: %d\n", i, th[i].media);
    }
    return 1;
}