/*********************************************************************************************************************************
*  Un processo padre crean N pari processi figli. CIascun processo figlio Pi è identificato da una variabile intera i 		     
*																																 
*  ci sono due casi:																											 
*																 																 
*    1. se l'argomento è a ogni processo con i pari manda un segnale SIGUSR1 al processo i+1 									 
*    2. se l'argomento è b ogni processo figlio con i < N/2 manda un segnale SIGUSR1 al processo i + N/2 		                 
**********************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N2 3
#define N N2*2

int pg[2];
int tabpid[N];
char arg1;

void handler(int signo){
    printf("Sono il processo %d e ho ricevuto il segnale %d\n", getpid(), signo);
}

void body_proc(int id){
    printf("Sono il processo %d con id = %d\n", getpid(), id);

    if(arg1 == 'a'){
        if(id % 2 == 0){ // Se id è pari
            int next_pid;
            read(pg[0], &next_pid, sizeof(next_pid));
            printf("Processo %d ha letto il PID del prossimo processo: %d\n", getpid(), next_pid);
            kill(next_pid, SIGUSR1);
        }
    }
    else{ // arg1 == 'b'
        if(id < N/2){ // Se id è minore della metà di N
            int next_pid;
            read(pg[0], &next_pid, sizeof(next_pid));
            printf("Processo %d ha letto il PID del prossimo processo: %d\n", getpid(), next_pid);
            kill(next_pid, SIGUSR1);
        }
    }
}

int main(int argc, char *argv[]){
    int i, status;

    if(argc != 2){
        printf("Eseguire di nuovo il programma con il secondo argomento\n");
        exit(-1);
    }

    arg1 = argv[1][0];

    if(arg1 != 'a' && arg1 != 'b'){
        printf("Il secondo argomento deve essere 'a' o 'b'\n");
        exit(-1);
    }

    if(pipe(pg) == -1){
        perror("pipe");
        exit(-1);
    }

    signal(SIGUSR1, handler); // Imposta la gestione del segnale SIGUSR1

    for(i = 0; i < N; i++){
        tabpid[i] = fork();
        
        if(tabpid[i] == -1){
            perror("fork");
            exit(-1);
        }
        else if(tabpid[i] == 0){
            // Codice del processo figlio
            close(pg[1]); // Chiude l'estremità di scrittura della pipe
            
            if(i != N-1){
                // Attende il PID del processo successivo
                int next_pid;
                read(pg[0], &next_pid, sizeof(next_pid));
            }
            body_proc(i);
            exit(0);
        }
        else{
    		// Codice del processo padre
   			 close(pg[0]); // Chiude l'estremità di lettura della pipe
    		// Invia il PID del processo figlio successivo
    		if(i != N-1){
       			 write(pg[1], &tabpid[i+1], sizeof(tabpid[i+1]));
       		if(i != 0) // Evita di inviare il segnale SIGUSR1 dal processo padre
           		 kill(tabpid[i], SIGUSR1);
    		}
		}		

    }

    // Invia il PID del primo processo figlio al processo padre
    write(pg[1], &tabpid[0], sizeof(tabpid[0]));

    // Attende la terminazione di tutti i processi figli
    for(i = 0; i < N; i++){
        wait(&status);
    }

    printf("Tutti i processi figli sono terminati\n");

    return 0;
}
