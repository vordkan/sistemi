#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREAD 8

int count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex per proteggere count

void *conta(void *threadID) {
    char find = *((char*) threadID);
    char carattere_letto;
    FILE *file;

    // apre il file
    file = fopen("test.txt", "r");

    // se non esiste da errore
    if (file == NULL) {
        printf("Impossibile aprire il file.");
        exit(0);
    }

    // cerca il carattere
    while ((carattere_letto = fgetc(file)) != EOF) {
        if (carattere_letto == find) {
            pthread_mutex_lock(&count_mutex); // Blocca il mutex prima di modificare count
            count++;
            pthread_mutex_unlock(&count_mutex); // Sblocca il mutex dopo aver modificato count
        }
    }

    // chiude il file
    fclose(file);
    printf("Ho contato: %d\n",count);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <character to find>\n", argv[0]);
        return 1;
    }

    char find = argv[1][0]; 

    pthread_t threads[NTHREAD];
    char taskids[NTHREAD]; 
    int rc, t;

    for (t = 0; t < NTHREAD; t++) {
        taskids[t] = t; 
        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, conta, (void*)&find);
        if (rc) {
            printf("ERROR, return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Attendi il completamento di tutti i thread
    for (t = 0; t < NTHREAD; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("Totale: %d\n", count); // Stampa il totale

    pthread_exit(NULL);
}
