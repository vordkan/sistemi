/*
   Scrivere un programma in che preso un argomento intero da linea di comando gestisca la seguente situazione.

   Genera Due figli A e B.
   Se l'argomento è pari allora invia un segnale SIGUSR1 alla ricezione del quale il figlio A calcola il cubo dell'argomento passato da linea di comando, 
   mentre B scrive un messaggio di arrivederci e termina .

   Se l'argomento è dispari invia un segnale di SIGUSR2 alla ricezione del quale il figlio B calcola il reciproco del numero passato come argomento ed invia un segnale
   SIGUSR1 al processo A e termina l'esecuzione. Il figlia A aspetta il SIGUSR1 scrive un messaggio di arrivederci e termina.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// variabili globali
int pidA, pidB, intero, segnale;

// gestore
void gestore(int signo){
   segnale = signo;
}

int main(int argc, char *argv[]){
   // variabili locali
   int cubo, argomento;
   float reciproco;
   signal(SIGUSR1, gestore);
   signal(SIGUSR2, gestore);

   argomento = atoi(argv[1]);
   printf("%d",argomento);
   // Creazione figlio A
   pidA  = fork();
   if(pidA == 0){
      pause();
      // segnale inviato dal padre
      if(segnale == SIGUSR1){
         cubo = argomento * argomento * argomento;
         printf("Figlio A: Cubo dell' argomento %d\n",cubo);
         exit(0);
      } else{
         printf("Figlio A: intero ricevuto è dispari... attendo un segnale\n");
         pause();
         if(segnale == SIGUSR1) printf("Figlio A: Segnare arrivato... termino\n");
      } 
   }

   // Creazione figlio B
   pidB = fork();

   if(pidB == 0){
      pause();
      if(segnale == SIGUSR1){
         printf("Figlio B: Argomento ricevuto è pari... arrivederci\n");
         exit(0);
      }
      else{
         reciproco = (float)1/argomento;
         printf("Figlio B: Reciproco calcolato %f\n", reciproco);
         sleep(2*argomento);
         kill(pidA,SIGUSR1);
         exit(0);
      }
   }

   // Padre
   if((pidA && pidB) != 0){
      sleep(2);
      if(argomento %2 == 0){
         kill(pidA, SIGUSR1);
         kill(pidB, SIGUSR1);
      }
      else{
         kill(pidA, SIGUSR2);
         kill(pidB, SIGUSR2);
      }
   }

   wait(NULL);
   wait(NULL);
   
   exit(0);
   printf("Processo padre terminato... arrivederci\n");
}