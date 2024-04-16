/*
SCRIVERE UN PROGRAMMA C CHE:
* CREA UN PROCESSO FIGLIOM STAMPA IL MESSAGGIO "IN ATTESA" ED ATTENDE LA TERMINAZIONE DEL FIGLIO.
* IL FIGLIO ESEGUE IL COMANDO "ls -l"
* QUANDO IL FIGLIO TERMINA, IL PADRE VISUALIZZA IL MESSAGGIO "NUOVO FIGLIO" E CREA UN SECONDO PROCESSO FIGLIO.
* IL SECONDO FIGLIO ASPETTA PER 5 SECONDI, STAMPA A VIDEO UN MESSAGGIO E TERMINA.
* QUANDO IL PROCESSO FIGLIO TERMINA IL PADRE STAMPA A VIDEO IL PID DEL PROCESSO TERMINATO.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    // Creazione del primo figlio
    if ((pid1 = fork()) < 0) {
        perror("Errore nella creazione del primo figlio");
        exit(-1);
    } else if (pid1 == 0) {
        printf("In attesa\n");
        execlp("ls", "ls", "-l", NULL); 
        perror("Errore nell'esecuzione di execlp");
        exit(-1);
    } else { 
        // Padre
        printf("Nuovo figlio: %d\n", pid1);
        waitpid(pid1, &status, 0); 
	
        // Creazione del secondo figlio
        if ((pid2 = fork()) < 0) {
            perror("Errore nella creazione del secondo figlio");
            exit(-1);
        } else if (pid2 == 0) { 
           // Secondo figlio
            sleep(5);
            printf("Messaggio del secondo figlio\n");
            exit(0);
            
        } else { 
            // Padre
            printf("Nuovo figlio: %d\n", pid2);
            waitpid(pid2, &status, 0); 
            printf("Processo figlio terminato: %d\n", pid2);
            exit(0);
        }
    }

    return 0;
}

