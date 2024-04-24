//foto esercizio 1
/*
   Il programma genera due figli A e B, se l'argomento è pari invia SIGUSR1 alla ricezione del quale il figlio A calcola il cubo del numero passatoc ome argomento
*/

// dichiarazione variabili
int pidA, pidB, intero, segnale;

void gestore(int signo)
