#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 8

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int min = 300;

typedef struct {
    int size;
    int **mat;
    int indice;
} Data;

int** creaMatrice(int n) {
    int i, j;
    int **mat = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++)
        mat[i] = (int*)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            mat[i][j] = rand() % 20;

    return mat;
}

void visualizzaMatrice(int n, int** mat) {
    printf("Matrice:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

void *azione(void *arg) {
    Data *data = (Data*)arg;
    int s = 0;
    for (int i = 0; i < data->size; i++) {
        s += data->mat[i][data->indice];
    }

    pthread_mutex_lock(&mutex);
    if (s < min) {
        min = s;
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Inserire un argomento durante l'avvio del programma\n");
        return 1;
    }
    int n = atoi(argv[1]);

    int** mat = creaMatrice(n);
    printf("Creazione matrice...\n");
    visualizzaMatrice(n, mat);

    pthread_t threads[MAX_THREADS];
    Data dati[MAX_THREADS];

    int num_threads = (n < MAX_THREADS) ? n : MAX_THREADS;

    for (int i = 0; i < num_threads; i++) {
        dati[i].size = n;
        dati[i].mat = mat;
        dati[i].indice = i;
        pthread_create(&threads[i], NULL, azione, (void*)&dati[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Il valore minimo delle somme delle colonne è: %d\n", min);

    return 0;
}
