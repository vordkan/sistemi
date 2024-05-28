/*
* SCRIVERE UN PROGRAMMA C IN CUI UN PROCESSO CREA UN PROCESSO FIGLIO
* IL PROCESSO FIGLIO CALCOLA LA SEQUENZA DI FIBONACCI DI ORDINE N (N<=12) E SCRIVE IL VALORE CALCOLATO SU UNA PIPE.
* QUANDO TERMINA RESTITUISCE IL VALORE CALCOLATO COME CODICE DI TERMINAZIONE.
* IL PADRE LEGGE IL VALORE CALCOLATO DALLA PIPE ED ESAMINA LO STATO DI TERMINAZIONE DEL FIGLIO:
*    - SE LO STATO DI TERMINAZIONE È RELATIVO AD UNA TERMINAZIONE CON SUCCESSO E IL VALORE LETTO DALLA PIPE È MINORE DI 50
*    - CREA UN SECONDO FIGLIO CHE ESEGUE IL COMANDO "LS -AL A.OUT".
*    - ATTENDE IL SECONDO FIGLIO, STAMPA UN MESSAGGIO E TERMINA; ALTRIMENTI STAMPA UN MESSAGGIO E TERMINA.
*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LETTURA     0
#define SCRITTURA   1

int fibo(int n){
    if(n <=1)
        return n;
    else
        return fibo(n-1) + fibo(n-2);
}

int main(int argc, char* argv[]){
    if(argc != 2){
        perror("Inserire la n vicino all' esecuzione\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);


    int fd[2];
    if (pipe(fd) == -1) {
        perror("Errore durante la creazione della pipe");
        exit(EXIT_FAILURE);
    }

    pid_t figlio1;
    figlio1 = fork();

    if(figlio1 < 0){
        perror("Figlio 1 non creato\n");
        exit(EXIT_FAILURE);
    }
    else if(figlio1 == 0){
        int result = fibo(n);
        close(fd[LETTURA]);
        write(fd[SCRITTURA], &result, sizeof(result));
        close(fd[SCRITTURA]);

        exit(0);
    }
    else{
        waitpid(figlio1, NULL, 0);
        int result;
        pid_t figlio2;

        close(fd[SCRITTURA]);
        read(fd[LETTURA], &result, sizeof(result));
        if(result < 50){
            figlio2 = fork();

            if(figlio2 < 0){
                perror("Errore nella creazione del figlio 2\n");
                exit(EXIT_FAILURE);
            }

            else if(figlio2 == 0){
                execlp("ls", "ls", "-al", "a.out", NULL);
                exit(0);
            }

            // Se sono il padre allora aspetto il figlio e lancio il messaggio "Secondo figlio completato"
            waitpid(figlio2, NULL, 0);

            printf("Arrivederci...\n");
            exit(0);
        }
        else{
            perror("Risultato maggiore di 50\n");
            exit(-1);
        }
    }
}