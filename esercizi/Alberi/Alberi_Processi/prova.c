#include <stdio.h>
#include <stdlib.h>

int main(){
    int i = 0;
    int prova = 0;

    if(prova == 0){
        printf("entrato nell' if ora incremento \n");
        printf("%d\n", prova);
        for(i = 0; i < 2; i++ ){
            prova ++;
            printf("ora incremento, prova = %d \n", prova);
        }
        printf("esco dal for \n");
        printf("%d\n", prova);
    }
    printf("esco dall'if \n");
    printf("%d\n", prova);
}