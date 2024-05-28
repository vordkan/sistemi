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
#include <pthread.h>


int* creaVettore(int n){
    int* v = (int*)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        v[i] = rand() % 20;
    }

    return v;
}

void visualizzaVettore(int *v, int n){
    for(int i = 0; i < n; i++){
        printf("%d\t", v[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Inserire altro argomento vicino l'avvio\n");
        return 0;
    }

    int n = atoi(argv[1]);

    if(n < 21){
        printf("L'argomento deve essere maggiore di 21 e un multiplo di 3\n");
        return 0;
    }

    if(n % 3 != 0){
        printf("L'argomento deve essere un multiplo di 3\n");
        return 0;
    }

    int *v = creaVettore(n);
    visualizzaVettore(v,n);

    return 0;
}