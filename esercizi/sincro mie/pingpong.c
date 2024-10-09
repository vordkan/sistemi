/*
Durante il campionato mondiale di ping pong si affrontano i giocatori di Italia e Cina. Il matche prevede che si:
- Affrontino a turno i dieci giocatori di ciascuna squadra.
- Tutte le partite possono giocarsi in contemporanea su dieci tavoli disponibili.
- I giocatori delle rispettive squadre formano due code prima di entrare nell'area con i tavoli.
- I giocatori di ambo le squadre sono indolenti e arrivano alla spicciolata, per cui quando arriva un giocatore controlla se un giocatore della squadra avversaria è disponibile, in tal caso
    entrano insieme, altrimenti attendono.
- Finita la partita i due giocatori sempre alla spicciolata si metteranno in coda fino a che ogni giocatore avrà giocato con tutti i giocatori della squadra avversaria.
*/

Italia(){
    // incremento il numero di giocatori italiani pronti a giocare
    lock(mutex)
    Italiano ++
    unlock(mutex)

    // creazione della coda Italiana
    wait(coda_Italia)

    // controllo se ci sono giocatori cinesi pronti a giocare
    if(Ciense > 0)
        signal(coda_Cina)

    // vado in mutua esclusione per controllare i tavoli disponibili ed occuparli
    lock(mutex)
    if(tavolo_disponibile > 0){
        // ciclo i tavoli per trovare uno libero
        for(i = 0 to 9){
            if(tavolo[i] == 0){
                // decremento il posto dei tavoli disponibili
                tavolo_disponibile --

                // lo occupo
                tavolo[i] = 1
                unlock(mutex)

                gioca()

                lock(mutex)
                // lascio il tavolo 
                tavolo_disponibile ++
                tavolo[i] = 0
                unlock(mutex)

                // faccio entrare il prossimo della coda
                signal(coda_Italia)

                // controllo se ho giocato con tutti i giocatori e mi restituisce un intero, 0 se ancora non ho giocato con tutti e 1 per aver giocato con tutti
                controllo = controllo_partite_giocate()

                if (controllo == 0){
                    signal(coda_Cina)

                    // mi rimetto in coda 
                    wait(coda_Italia)
                }
                else{
                    // decremento la variabile delle persone che devono giocare perchè ormai non ne ha più bisogno di giocare
                    lock(mutex)
                    Italiano --
                    unlock(mutex)
                    exit()
                }
            }
        }
    }        
}



Cina(){
    // incremento il numero di giocatori Cinesi pronti a giocare
    lock(mutex)
    Cinese ++
    unlock(mutex)

    // creazione della coda cinese
    wait(coda_Cina)

    // controllo se ci sono giocatori Italiani pronti a giocare
    if(Italiano > 0)
        signal(coda_Italia)

    // vado in mutua esclusione per controllare i tavoli disponibili ed occuparli
    lock(mutex)
    if(tavolo_disponibile > 0){
        // ciclo i tavoli per trovare uno libero
        for(i = 0 to 9){
            if(tavolo[i] == 0){
                // decremento il posto dei tavoli disponibili
                tavolo_disponibile --

                // lo occupo
                tavolo[i] = 1
                unlock(mutex)

                gioca()

                lock(mutex)
                // lascio il tavolo 
                tavolo_disponibile ++
                tavolo[i] = 0
                unlock(mutex)

                // faccio entrare il prossimo della coda
                signal(coda_Cina)

                // controllo se ho giocato con tutti i giocatori e mi restituisce un intero, 0 se ancora non ho giocato con tutti e 1 per aver giocato con tutti
                controllo = controllo_partite_giocate()

                if (controllo == 0){
                    signal(coda_Italia)
                    
                    // mi rimetto in coda 
                    wait(coda_Cina)
                }
                else{
                    // decremento la variabile delle persone che devono giocare perchè ormai non ne ha più bisogno di giocare
                    lock(mutex)
                    cinese --
                    unlock(mutex)
                    exit()
                }
            }
        }
    }        
}