/*
    Scrivere un programma in ambiente linux che implementi, stile shell bash,
    la seguente pipeline inserita da linea di comando
    ls -l
    wc -c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LETTURA 0
#define SCRITTURA 1
int main(){
    int fd[2];
    pid_t figlio1, figlio2;

    // creiamo prima la pipe
    if(pipe(fd) == -1){
        perror("Errore durante la creazione della pipe\n");
        exit(EXIT_FAILURE);
    }

    // creiamo il primo processo per scrivere nella directory?
    figlio1 = fork();

    if(figlio1 < 0){
        perror("Figlio non creato\n");
        exit(EXIT_FAILURE);
    }
    else if(figlio1 == 0){
        printf("Sono il figlio1\n");

        //chiudo la lettura della pipe
        close(fd[LETTURA]);

        //duplico la pipe per la scrittura
        dup2(fd[SCRITTURA], STDOUT_FILENO);

        //chiudo la scrittura
        close(fd[SCRITTURA]);

        //esecuzione del comando del primo figlio
        execlp("ls","ls","-l", NULL);

        exit(0);
    }

    // Creazione del secondo processo per leggere nella directory
    figlio2 = fork();

    if(figlio2 < 0){
        perror("Figlio non creato\n");
        exit(EXIT_FAILURE);
    }
    else if(figlio2 == 0){
        printf("Sono il secondo figlio\n");

        close(fd[SCRITTURA]);
        dup2(fd[LETTURA], STDIN_FILENO);
        close(fd[LETTURA]);

        execlp("wc", "wc", "-c", NULL);

        exit(0);
    }

    close(fd[SCRITTURA]);
    close(fd[LETTURA]);

    printf("Aspetto che i figli terminano\n");

    waitpid(figlio1,NULL,0);
    printf("Figlio 1 terminato\n");

    waitpid(figlio2,NULL,0);
    printf("Figlio 2 terminato\n");
}
