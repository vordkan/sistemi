#include <stdio.h>
#include <unistd.h>

int glob = 20;
int pid = 0;

int main() {
    int i = 0;
    for (i = 2; i < 4; i++) {
        pid = fork(); // creo un nuovo figlio
        if (pid == 0) {
            glob = glob * 2;
            sleep(1);
            printf("valore di glob nel processo figlio = %d\n", glob); // Stampa nel processo figlio
            return 0; // Termina il processo figlio dopo la stampa
        }
        glob = glob - 1;
    }
    printf("valore di glob nel processo padre = %d\n", glob); // Stampa nel processo padre
    return 0;
}

