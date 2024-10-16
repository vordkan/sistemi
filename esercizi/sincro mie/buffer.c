
/* Un sistema è composto di un buffer di N posizioni, 2*N processi attivi ed un processo coordinatore
   Il processo coordinatore estrae uno dopo l'altro in maniera casuale i numeri da 1 a N e ad
   ogni estrazioni i processi competono per aggiudicardi l'accesso alla posizione corrispondente
   del buffer, scrivendone il proprio PID.
   Un processo che ha scritto il proprio PID nel buffer NON partecipa più alla contesa. 
   Quando tutte le posizioni del buffer sono state assegnate, il coordinatore si alterna con l'ultimo
   processo che ha avuto accesso al buffer nel leggere e stampare, uno alla volta, il contenuto del buffer.
*/

   processo_coordinatore(){
      // aspetto l'assegnazione di tutti i numeri
      while(completato){
         // controlla se il numero generato non è stato assegnato
         while(assegnato){
            //estrae il numero in maniera casuale
            lock(mutex)
            numero_estratto = rand(1,N)
            unlock(mutex)
            // ciclo su tutto il buffer per vedere se la posizione che sto controllando non è stata riempita da un pid
            lock(mutex)
            // se è vuoto segnalo che i processi attivi possono segnare il loro pid
            if(buffer[numero_estratto] == 0){
               signal(estratto)
               // mi conservo la variabile conta per vedere quando arrivo all'ultimo processo
               conta ++  
            }
            // esco dal while
            unlock(mutex)
            // aspetto che il processo attivo ha scritto il suo pid prima di continuare
            wait(scritto)
            signal(assegnato)
         }
         if(conta == N){
            // quando arriva a N mi segno la posizione per recuperare il pid dell'ultimo processo
            ultima_posizione = numero_estratto
            // se il contatore è arrivato ad N allora esco dal ciclo di assegnazione 
            signal(completato)
         }
      }
      // ora mi devo alternare per leggere e per stampare
      lock(mutex)
      for(i=0; i<N; i+2){
         if(i == 0){
            stampa(buffer[i])
            signal(last_process)
         }
         wait(processo_coordinatore)
         stampa(buffer[i]) 
         unlock(mutex)
         signal(last_process)
      }
   }

   processi_attivi(){
      // aspetto che il processo_coordinatore estrae un numero
      wait(estratto)
      // vado a scrivere il mio pid nella posizione che ho recuperato
      lock(mutex)
      buffer[numero_estratto] = pid()
      unlock(mutex)
      // dico al coordinatore che può procedere con altri numeri
      singal(scritto)
      // se sono l'ultimo allora procedo ad alternarmi con il coordinatore
      lock(mutex)
      if(numero_estratto == ultima_posizione){
         for(i=1; i<N; i+2){
            wait(last_process)
            stampa(buffer[i])
            signal(processo_coordinatore)
         }
      }
      unlock(mutex)
      // altrimenti esco
      else{
         exit()
      }
   }