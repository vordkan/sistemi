		/*********************************************************************************************************************************
		*  Un processo padre crean N pari processi figli. CIascun processo figlio Pi è identificato da una variabile intera i 		 *
		*																 *
		*  ci sono due casi:														 *
		*																 *
		*    1. se l'argomento è a ogni processo con i pari manda un segnale SIGUSR1 al processo i+1 					 *
		*    2. se l'argomento è b ogni processo figlio con i < N/2 manda un segnale SIGUSR1 al processo i + N/2 			 *
		**********************************************************************************************************************************/

#include <stdio.h>

void handler(int signo){
  printf("sono il processo %d e ho ricevuto il segnale %d\n",getpid(),signo);
}

int body_proc(int id){
  printf("Sono il processo %d con id=%d\n!",getpid(),id);
}



