/*
    Nella sala recruitment di una grande azienda informatica, durante una sessione di interview possono prendere posto al più N candidati, 
    mentre i restanti candidati prenderanno parte alla sessione di interview successiva.

    Ogni candidato che ha trovato posto sarà chiamato al tavolo delle interview.

    L'addetto alle risorse umane attende fino che è disponibile un candidato.

    Terminata l'intervista il candidato lascia il tavolo e la sala facendo posto al prossimo candidato.

    Le sessioni di interview terminano quando non ci sono più candidati in attesa. 

    Proporre una soluzione e discutere eventuali problemi di deadlock.
*/

candidato(){
    // incremento il numero di candidati presenti
    signal(candidato)

    // entro in mutua esclusione per controllare i posti disponibili e nel caso ci siano li decrementa
    lock(mutex)
    if(posto_disponibile > 0){
        siediti()
        posto_disponibile --
        unlock(mutex)
        // aspetto la chiamata al tavolo delle interviste
        wait(tavolo_interview)
        // aspetto la fine 
        wait(fine_interview)
        // entro in mutua esclusione per liberare il posto
        lock(mutex)
        alzati()
        posto_disponibile ++
        unlock(mutex)
    } 
    else{
        // dico che ci sono candidati in attesa per la prossima interview
        in_attesa ++
        unlock(mutex)
        // aspetto la prossima sessione
        wait(prossima_interview)
        // aspetto di essere chiamato per l'intervista
        wait(tavolo_interview)
        // aspetto che finisca
        wait(fine_interview)
    }
}

HR(){
    while(true){
        // entro in mutua esclusione per controllare se ci sono candidati per fare l'intervista
        lock(mutex)
        if(candidato > 0){
            unlock(mutex)
            // segnalo che si può avvicinare al tavolo
            signal(tavolo_interview)
            // fa l'intervista
            intervista()
            // se ne deve andare dal tavolo
            signal(fine_interview)
            // decremento il numero di candidati
            wait(candidato)
        }

        else{
            unlock(mutex)
            // in mutua esclusione controllo se ci sono candidati in attesa
            lock(mutex)
            if(in_attesa > 0){
                unlock(mutex)
                // chiamo i candidati che stanno aspettando la prossima sessione
                signal(prossima_interview)
                // chiamo il candidato al tavolo
                signal(tavolo_interview)
                // finisce l'intervista
                signal(fine_interview)
                // entro in mutua esclusione per decrementare le persone in attesa
                lock(mutex)
                in_attesa --
                unlock(mutex)
            }
            else{
                exit()
            }
        }
    }
}