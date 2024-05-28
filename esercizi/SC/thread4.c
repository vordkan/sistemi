/**
 * Si realizzi un programma C e Posix in ambiente Linux che, impiegando la libreria Pthread, 
 * crei un vettore di interi di dimensione n, dove n>=24 e multiplo di 4,  
 * è un argomento passato da riga di comando.  
 * Calcolati i valori medi degli elementi contenuti nei quattro sottovettori di taglia n/4,  
 * il programma deve determinare, impiegando quattro thread, la somma del numero di elementi minori  
 * del valore medio in ciascun sottovettore.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NT 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread[NT];

typedef struct{
    int size;
    int *conta;
    int *v;
    int media;
}Dati;

void* minore(void *arg){
     Dati* data = (Dati*)arg;

    for(int i = 0; i < data->size; i++){
        pthread_mutex_lock(&mutex);
        if(data->v[i] < data->media)
            (*data->conta)++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int* creavettore(int n){
    int *v = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        v[i] = rand() % 255;
    return v;
}

void leggivettore(int n, int *v){
    for(int i = 0; i < n; i++)
        printf("[%d]", v[i]);
}

double calcolamedia(int n, int *v){
    int i = 0, somma = 0;
    double media = 0.0;

    for(i = 0; i < n; i++)
        somma += v[i];
    media = somma / n;

    return media;
}

int main(int argc, char *argv[]){
    int n = 0;

    if(argc != 2){
        printf("Inserire un argomento che sia maggiore di 24 e un multiplo di 4");
        return 1;
    }
    
    n = atoi(argv[1]);

    if (n < 24 || n % 4 != 0){
        printf("Inserire un argomento che sia maggiore di 24 e un multiplo di 4");
        return 1;
    }

    int *v = creavettore(n);
    leggivettore(n,v);
    double med = calcolamedia(n,v);

    printf("Media trovata: %f", med);

    // Array per memorizzare il numero di elementi maggiori della media per ciascun thread
    int counts[NT] = {0};

    Dati dati[NT];

    for(int i = 0; i < NT; i++){
        dati[i].media = med;
        dati[i].size  = n / NT;
        dati[i].conta = &counts[i];
        dati[i].v     = &v[i * (n / NT)];

        pthread_create(&thread[i], NULL, minore, (void*)&dati[i]);

    }

    for(int i = 0; i < NT; i++)
        pthread_join(thread[i], NULL);

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