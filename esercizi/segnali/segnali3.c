/****************************************************************************************************************************************************************************
* Si scriva un programma in C che utilizzando la SC di unix, prevesa la seguente sintassi: esame N N1 N2 C 						                    *
* dove: 																				    *
* esame è il nome dell'eseguibile da generare. 																    *
* N, N1, N2 sono interi positivi. 																	    *
* C è il nome di un comando. 																		    *
* 																					    *
*  Il comando dovrà funzionare nel modo seguente: 														            *
*  un processo padre P0 deve creare 2 processi figli: P1 e P2    												            *
* 																					    *
* Il figlio P1 deve aspettare N1 secondi e successivamente eseguire il comando C 											    *
* il figlio P2 dopo N2 secondi dalla sua creazione dovrà provocare la terminazione del processo fratello P1 e successivamente terminare. 				    *
* nel frattempo, P2 deve periodicamente sincronizzarsi con il padre P0. 												    *
* il padre P0 dopo aver creato i figli si pone in attesa di segnali da P2: per ogni segnale ricevuto dovrà stampare il proprio pid. all' n esimo segnale ricevuto ...       *
*****************************************************************************************************************************************************************************/


