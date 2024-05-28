#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 6
#define ELEMENTO 2

int mat[N][N];
int found = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void generaMat(){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mat[i][j] = rand() % 100; 
        }
    }
}

void stampaMat(){
    printf("Matrice generata:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

void* search(void* arg) {
    int row = *((int*)arg); 
    int i;

    // Cerca l'elemento nella riga specificata
    for (i = 0; i < N; i++) {
        if (mat[row][i] == ELEMENTO) {
            pthread_mutex_lock(&mutex);
            found = 1; 
            pthread_mutex_unlock(&mutex);
            if(found) printf("Elemento trovato nella riga %d in posizione %d\n", row, i);
            else printf("Elemento non trovato\n");
            return NULL; 
        }
    }
    return NULL;
}

int main(){
    pthread_t threads[N];
    int i;

    generaMat();
    stampaMat();

    // Crea e avvia i thread
    for (i = 0; i < N; i++) {
        int* row = malloc(sizeof(int)); 
        *row = i;
        pthread_create(&threads[i], NULL, search, row);
    }

    // Attendi che uno qualsiasi dei thread trovi l'elemento
    for (i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
