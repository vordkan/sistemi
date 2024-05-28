/*
Scrivere un programma C Posix, in ambiente Unix/Linux che implementi la seguente comunicazione:

Un processo padre genera un numeri casuali nell’intervallo [1,10] e li invia ad un processo figlio fino a quando scade un timer di N secondi, con N
fornito da riga di comando.

Il processo figlio normalizza i numeri nell’intervallo [0,1] e li restituisce al processo padre, comunicandogli l’ultimo numero inviato con un segnale SIGUSR1

Il padre, ricevuto il segnale termina il processo figlio e stampa i numeri normalizzati
*/

