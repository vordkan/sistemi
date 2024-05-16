/**
 * Si realizzi un programma in C e Posix sotto Linux che,
 * con l’ausilio della libreria Pthread
 * 
 * • lancia n thread per calcolare la somma degli elementi
 *   di ciascuna riga di una matrice nxn di interi generati
 *   casualmente in un intervallo [0,255], allocata dinamicamente
 * 
 * • Il calcolo della somma degli elementi di ciascuna riga
 *   deve essere effettuato concorrentemente su tutte le 
 *   righe, secondo la seguente modalità:
 *      
 *    -> il thread i-esimo con indice i pari, calcola la somma degli 
 *       elementi di indice pari della riga i-esima
 * 
 *    -> il thread con indice i dispari, calcola la somma degli
 *       elementi di indice dispari della riga i-esima.
 * 
 * • Calcolate le somme parziali, si provvederà a ricercarne il minimo ed a stamparlo a video.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 4

int minimo = __INT_MAX__;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
    int **matrice;
    int size;  
    int indice;
}Dati;

void* somma(void *arg){
    Dati *td = (Dati*)arg;
    int somma = 0;

    for(int j = 0; j < td->size; j++){
        if(td->indice % 2 == 0){
            somma += td->matrice[td->indice][j];
        }
        else{
            somma += td->matrice[td->indice][j];
        }
    }
    
    pthread_mutex_lock(&mutex);
    if (somma < minimo) {
        minimo = somma;
    }
    pthread_mutex_unlock(&mutex);
}



int** creamatrice(int n){
    int **m = (int**)malloc(n * sizeof(int*)); // Correzione qui

    for(int i = 0; i < n ; i++){
        m[i] = (int*)malloc(n * sizeof(int));
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            m[i][j] = rand()%20;
        }
    }
    return m;
}


void leggimatrice(int **m, int n){
    
    printf("Matrice creata:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
           printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}

int main(){

    int n = N;

    int **matrice = creamatrice(n);
    leggimatrice(matrice,n);

    pthread_t thread[n];
    Dati td[n];

    for(int i=0; i<n; i++){
        td[i].size = n;
        td[i].matrice = matrice;
        td[i].indice = i;

        pthread_create(&thread[i], NULL, somma, (void*)&td[i]);
    }

    for(int i = 0; i < n; i++){
        pthread_join(thread[i],NULL);
    }

    printf("Il minimo trovato è: %d\n", minimo );

    return 0;
}