#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 8


int somma = 0;
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
int minimo = 300;

typedef struct{
    int size;
    int **mat;
    int indice;
}Dati;

int** creaMatrice(int n){
    int **m = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        m[i] = (int*)malloc(n * sizeof(int));
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            m[i][j] = rand()%20;
        }
    }

    return m;
}

void visualizzaMatrice(int **m, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}

void *routine(void *arg) {
    Dati *data = (Dati*)arg;
    for (int i = 0; i < data->size; i++) {
        s += data->mat[i][i];
    }

    pthread_exit(NULL);
}



int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Inserire un argomento vicino all'avvio\n");
        return 1;
    }

    int n = atoi(argv[1]);

    int **mat = creaMatrice(n);
    visualizzaMatrice(mat,n);

    pthread_t thread[MAX_THREADS];
    Dati dati[MAX_THREADS];

    for(int i = 0; i < MAX_THREADS; i++){
        dati[i].size = n;
        dati[i].mat = mat;
        dati[i].indice = i;

        pthread_create(&thread[i], NULL, routine, (void*)&dati[i]);
    }

    for(int i = 0; i < MAX_THREADS; i++){
        pthread_join(thread[i], NULL);
    }

    printf("Diagonale %d\n", somma);


}