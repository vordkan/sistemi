/**
 * Si realizzi un programma C e Posix in ambiente Linux che, impiegando la libreria Pthread, 
 * crei un vettore di interi di dimensione n, dove n>=21 e multiplo di 3,  
 * è un argomento passato da riga di comando.  
 * Calcolato il valore medio degli elementi contenuti nel vettore,    
 * il programma deve determinare, impiegando tre thread, il numero di elementi maggiori 
 * del valore medio, rispettivamente nei tre sottovettori di dimensioni n/3
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NT 3

typedef struct{
    int *v;
    int size;
    double media;
    int *count;
}ThreadData;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void *maggiore(void* arg){
    ThreadData* data = (ThreadData*)arg;

    for(int i = 0; i < data->size; i++){
        pthread_mutex_lock(&mutex);
        if(data->v[i] > data->media)
            (*data->count)++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}


double media(int n, int *v){
    int i = 0, somma = 0;
    double media = 0.0;

    for(i = 0; i < n; i++)
        somma += v[i];
    media = somma / n;

    return media;
}

int* creavettore(int n){
    int* v = (int*)malloc(n * sizeof(int));

    if(v == NULL){
        printf("errore");
        return 0;
    }

    for(int i = 0; i < n; i++)
        v[i] = rand() % 100;

    return v;
}

void visualizza(int n, int* v){
    for(int i = 0; i < n; i++)
        printf("[%d] ", v[i]);
}

int main(int argc, char *argv[]){
    int n = 0;
    pthread_t thread[NT];
    
    if(argc != 2) printf("Inserire argomenti...\n");

    n = atoi(argv[1]);

    if(n < 21){
        printf("Inserire un numero maggiore di 21\n");
        return -1;
    } 
    else if(n % 3 == 1){
        printf("Il numero deve essere un multiplo di 3\n");
        return -1;
    }

    int* v = creavettore(n);
    visualizza(n, v);

    double med = media(n,v);

    // Array per memorizzare il numero di elementi maggiori della media per ciascun thread
    int counts[NT] = {0};

    ThreadData threadArgs[NT];

    for (int i = 0; i < NT; i ++){
        threadArgs[i].v = &v[i * (n / NT)];
        threadArgs[i].size = n / NT;
        threadArgs[i].media = med;
        threadArgs[i].count = &counts[i];

        pthread_create(&thread[i], NULL, maggiore, (void*)&threadArgs[i]);
    }

    for(int i = 0; i < NT; i ++){
        pthread_join(thread[i],NULL);
    }

    // Calcolo del totale dei valori maggiori della media
    int totalAboveMean = 0;
    for (int i = 0; i < NT; i++) {
        totalAboveMean += counts[i];
    }
    
    printf("Total elements above mean: %d\n", totalAboveMean);
    
    // Rilascio della memoria
    free(v);
    
    return 0;
}