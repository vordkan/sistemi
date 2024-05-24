/*
* SCRIVERE UN PROGRAMMA C IN CUI UN PROCESSO CREA UN PROCESSO FIGLIO
* IL PROCESSO FIGLIO CALCOLA LA SEQUENZA DI FIBONACCI DI ORDINE N (N<=12) E SCRIVE IL VALORE CALCOLATO SU UNA PIPE.
* QUANDO TERMINA RESTITUISCE IL VALORE CALCOLATO COME CODICE DI TERMINAZIONE.
* IL PADRE LEGGE IL VALORE CALCOLATO DALLA PIPE ED ESAMINA LO STATO DI TERMINAZIONE DEL FIGLIO:
*    - SE LO STATO DI TERMINAZIONE È RELATIVO AD UNA TERMINAZIONE CON SUCCESSO E IL VALORE LETTO DALLA PIPE È MINORE DI 50
*    - CREA UN SECONDO FIGLIO CHE ESEGUE IL COMANDO "LS -AL A.OUT".
*    - ATTENDE IL SECONDO FIGLIO, STAMPA UN MESSAGGIO E TERMINA; ALTRIMENTI STAMPA UN MESSAGGIO E TERMINA.
*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int fibonacci(int n){
   if(n <=1)
      return n;
   else
   	return fibonacci(n-1) + fibonacci(n-2);
}


int main(){
   pid_t pid1, pid2;
   int status;
   int nrand;
   
   srand(time(NULL));
   nrand = 1 + rand() % (12 - 1 + 1);
   
   // Creazione del primo figlio
   pid1 = fork();
   
   // Se non è stato creato allora manda un messaggio di errore
   if(pid1 < 0 ){
      perror("Errore nella fork di pid1\n");
      exit(-1);
   // Se è il figlio la funzione di fibonacci e restituisce il valore come uscita   
   } else if( pid1 == 0){
       int result = fibonacci(nrand);
       exit(result);
   // Se è il padre aspetta il figlio    
   } else{
       waitpid(pid1, &status, 0);
       // Se il risultato l'uscita del figlio 1 è minore di 50 
       if(WIFEXITED(status) && WEXITSTATUS(status) < 50){
          // Creo il secondo figlio
          pid2 = fork();
          // Se il secondo figlio non è stato creato invio un messaggio di errore          
          if(pid2 < 0){
             perror("Errore nella fork di pid2\n");
             exit(-1);
             // Se è il secondo figlio
          } else if(pid2 == 0){
              // Lancio il comando ls -al a.out
              execlp("ls", "ls", "-al", "a.out", NULL);
              // In caso di errore del comando
              perror("Errore nell'esecuzione del comando");
              exit(-1);
          } else{
              // Se sono il padre allora aspetto il figlio e lancio il messaggio "Secondo figlio completato"
              waitpid(pid2, NULL, 0); 
              printf("Secondo figlio completato\n");
              exit(0);
          }
          
       } else printf("Il primo figlio ha terminato con un valore maggiore di 50\n");
   }
}
