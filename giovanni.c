
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


/* In un sistema sono attivi N processi dotati di un credito C.
   Ogni processo genera un numero casuale P in [1...C) e verifica se il proprio P è
   maggiore di quello degli altri processi (a parità di P vince il processo con il PID
   minore).
   Il processo vincitore (quello con P maggiore) aggiunge al proprio credito C le quantità
   P generate da tutti gli altri processi, che invece sottraggono al proprio credito C la 
   quantità P generata.
   Un processo con credito C=0 termina
*/

//Processi da sincronizzare: Processo(i)

/*Azioni dei Processi:
  1)Ogni processo genera un numero casuale P in [1...C]
  2)Ogni processo verifica se il proprio P è maggiore di quello degli altri
  3)Il processo vincitore aggiunge al proprio credito C le quantità P generate da tutti gli altri
  4)Chi invece perde sottrae al proprio credito C le quantità generate da tutti gli altri
  5)Un processo con credito C=0 perde e termina.
*/

processo(i) {
   //Continua a generare numeri solo finché C>0
   while(C[i] > 0) {
      //Genero un numero casuale P
      numero_casuale = rand(1,C)

      //Associo il numero generato a quel processo
      P[i] = numero_casuale

      //Mi trovo il processo con il P maggiore
      P_maggiore = max(P)
      
      wait(barrier)
      //Verifico se il P è meggiore di quello degli altri
         if(numero_generato == P_maggiore){
            for(j = 0 to N){
                if(i != j){
                    credito[j] -= P[j]
                }
                else{
                    credito[i] += P[j]
                }
            }
            signal(barrier)
         }
   }
   exit() 
}


/*
    Ad una fiera medievale è in atto un gioco.
    L'armiere pone M spade su un bancone che N cavalieri (N>M) devono accaparrarsi una spada ciascuno quanto prima.
    Chi riesce a prendere la propria spada attende gli altri cavallieri che riescono a prendere la spada.
    Mentre coloro i quali sono rimasti senza attendono il prossimo giro. 
    Il prossimo giro ha inizio solo dopo che tutti i cavalieri hanno pesato le spade, decretando quale è il vincitore con la spada più pesante e poi restituendo la spada al cavaliere.
    Il gioco termina quando N cavalieri hanno vinto il gioco.
    Il cavaliere che ha vinto il giro precedente salta un turno. 
    Usare semafori e variabili di condizione.
*/

//Processi da sincronizzare: Armiere & Cavaliere

/* Azioni dell'Armiere:
   1) Aspetta il segnale che è iniziato il prossimo giro
   2) Posa M spade
   3) Aspetta che i cavalieri prendano le spade dal bancone
   4) Manda il segnale che è iniziato il turno

*/

/* Azioni del Cavaliere:
   1) Aspettano il segnale che è iniziato il turno
   2) Cercano di prendere una spada
   3) Se riesce a prendere una spada attende che tutti gli altri cavalieri riescano a prenderne una
   4) Se invece non riescono a prendere la spada, aspettano il prossimo giro
   5) Una volta prese le spade, i cavalieri pesano le spade decretando qual è quella più pesante
      restituendola poi al cavaliere
   6) Il gioco termina quando tutti gli N cavalieri hanno vinto il gioco
   7) Il cavaliere che ha vinto il giro precedente salta un turno
*/

armiere() {
   //Ciclio finché non finisce il gioco
   while(gioco_in_corso) {
      //Manda il segnale che tuttwe le spade sono state posate
      signal(spade_posate)

      //Aspetta che i cavalieri finiscano il proprio turno
      wait(fine_turno)

      //Il gioco finisce quando N cavalieri hanno vinto
      wait(mutex)
      if(calvalieri_vincenti == N) {
         signal(mutex)
         gioco_in_corso = 0
      }
   }
}

cavaliere(i) {
   //Aspetta che l'armiere posi le spade
   wait(spade_posate)

   //Prendo una spada se disponibile
   wait(mutex)
   if(spade_disp > 0) {
      spade_disp--
      signal(mutex)
   }

   //Segnalo che ho preso una spada
   wait(mutex)
   spade_prese++
   signal(mutex)

   //Se tutti i cavalieri hanno preso una spada imposto a vero il valore del turno
   wait(mutex)
   if (spade_prese == M) {
      //imposto a vero il turno
      inizio_turno = 1

      signal(mutex)
      signal(pronti_a_giocare)
   }

   //Aspetto che tutti i cavalieri abbiano preso una spada prima di giocare
   wait(pronti_a_giocare)

   //Verifico che tutti gli altri giocatori ne abbiano presa una
   while(inizio_turno == 1) {
      //Peso le spade dato che è inziato il turno
      my_peso = pesa_spada()

      //Variabile per confrontare la spada che pesa di più
      peso_max = peso_max() 

      //Verifico se la mia spada è quella più pesante
      if (my_peso == peso_max) {
         //Ho vinto il turno
         cavalieri_vincenti++

         wait(mutex)

         //Restituisco la spada
         spade_disp++

         signal(mutex)

         exit()
      }
      else {
         wait(mutex)

         //Se ho perso poso la spada e basta
         spade_disp++

         signal(mutex)

         exit()
      }

      //Finisco il turno
      inizio_turno = 0

      //Segnalo all'armiere che è finito il turno
      signal(fine_turno)
   }
   else {
      //Non ha preso la spada, quindi aspetta il prossimo turno
      wait(next_turn)

         //Aspetta che l'armiere posi le spade
   wait(spade_posate)

   //Prendo una spada se disponibile
   wait(mutex)
   if(spade_disp > 0) {
      spade_disp--
      signal(mutex)
   }

   //Segnalo che ho preso una spada
   wait(mutex)
   spade_prese++
   signal(mutex)

   //Se tutti i cavalieri hanno preso una spada imposto a vero il valore del turno
   wait(mutex)
   if (spade_prese == M) {
      //imposto a vero il turno
      inizio_turno = 1

      signal(mutex)
      signal(pronti_a_giocare)
   }

   //Aspetto che tutti i cavalieri abbiano preso una spada prima di giocare
   wait(pronti_a_giocare)

   //Verifico che tutti gli altri giocatori ne abbiano presa una
   while(inizio_turno == 1) {
      //Peso le spade dato che è inziato il turno
      my_peso = pesa_spada()

      //Variabile per confrontare la spada che pesa di più
      peso_max = peso_max() 

      //Verifico se la mia spada è quella più pesante
      if (my_peso == peso_max) {
         //Ho vinto il turno
         cavalieri_vincenti++

         wait(mutex)

         //Restituisco la spada
         spade_disp++

         signal(mutex)

         exit()
      }
      else {
         //Se ho perso poso la spada e basta
         spade_disp++

         wait(mutex)

         signal(mutex)

         exit()
      }

      //Finisco il turno
      inizio_turno = 0

      //segnalo all'armiere che è finito il turno
      signal(fine_turno)
   }
}