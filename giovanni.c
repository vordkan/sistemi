
/* Un sistema è composto di un buffer di N posizioni, 2*N processi attivi ed un processo coordinatore
   Il processo coordinatore estrae uno dopo l'altro in maniera casuale i numeri da 1 a N e ad
   ogni estrazione i processi competono per aggiudicardi l'accesso alla posizione corrispondente
   del buffer, scrivendone il proprio PID.
   Un processo che ha scritto il proprio PID nel buffer NON partecipa più alla contesa. 
   Quando tutte le posizioni del buffer sono state assegnate, il coordinatore si alterna con l'ultimo
   processo che ha avuto accesso al buffer nel leggere e stampare, uno alla volta, il contenuto del buffer.
*/

//Processi di sincronizzare: Processo Coordinatore & Processi Attivi

/* Azioni dei Processi attivi (2*N):
   1) Competono per aggiudicarsi l'accesso alla posizione corrispondente
      al numero estratto dal coordinatore
   2) Scrivono il proprio PID al suo interno
   3) Se il processo ha già scritto il proprio PID nel buffer NON partecipa più alla contesa.
*/

/* Azioni del Processo coordinatore:
   1) Estrae uno dopo l'altro i numeri in maniera casuale da 1 a N
   2) Una volta che tutte le posizioni del buffer sono assegnate si alterna con l'ultimo
      processo attivo che ha avuto accesso al buffer
   3) Legge e stampa alternandosi il contenuto del buffer
*/


processo_coordinatore() {
   while(completato) {
      //Controlla che il numero generato non sia già stato estratto
      while(assegnato) {
      //Estrae in maniera casuale i numeri da 1 ad N
      estratto = rand(1,N)

      lock(mutex)
      //Se è vuota segnala ai processi attivi che poossono scrivere il proprio PID
      if(buffer[estratto] == 0) {
         signal(scrivi)
         //Salva la variabile per vedere quando si arriva all'ultimo processo
         contatore++
      }
      unlock(mutex)
      //aspetto che il processo abbia finito di scrivere il suo pid
      wait(scritto)

      //esco
      signal(assegnato)
      }
      if(contatore == N) {
        //Prendo l'ultimo processo che ha avuto accesso al buffer
        ultimo_processo = estratto

        //Finite le posizioni nel buffer e quindi può uscire
        signal(completato)
      }
   }
   //Si alterna con l'ultimo processo che ha avuto accesso per leggere e stampare
   lock(mutex)
   for(i=0 to N) {
      if(i  == 0){
         stampa(buffer[0])
         signal(ultimo_processo)
      }
      //aspetto che l'ultimo processo legga
      wait(processo_coordinatore)
      //ora stampo io
      stampa(buffer[i])
      unlock(mutex)
      //Segnalo che ho finito di stampare
      signal(ultimo_processo)
   }
}

processi_attivi() {
   //Aspettano che arrivi un numero estratto
   wait(scrivi)
   
   //scrivono il proprio PID all'interno
   lock(mutex)
   buffer[estratto] = getpid()
   unlock(mutex)

   //segnalo che ha finito di scrivere
   signal(scritto)

   //alterno la lettura e la scrittura se sono l'ultimo
   lock(mutex)
   if(estratto == ultimo_processo) {
    for(i=0 to N) {
        //aspetto che l'ultimo processo legga
        wait(ultimo_processo)
        //ora stampo io
        stampa(buffer[i])
        unlock(mutex)
        //Segnalo che ho finito di stampare
        signal(prrocesso_coordinatore)
    }
   }
   unlock(mutex)
   //altrimenti se ho già scritto il PID esco
   else {
    exit()
   }
}


7
