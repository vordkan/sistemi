/*
    Ad una fiera medievale è in atto un gioco.
    L'armiere pone M spade su un bancone che N cavalieri (N>M) devono accaparrarsi una spada ciascuno quanto prima.
    Chi riesce a prendere la propria spada attende gli altri cavallieri che riescono a prendere la spada.
    Mentre coloro i quali sono rimasti senza attendono il prossimo giro. 
    Il prossimo giro ha inizio solo dopo che tutti i cavalieri hanno pesato le spade, decretando quale è il vincitore con la spada più pesante e poi restituendo la spada all'armiere.
    Il gioco termina quando N cavalieri hanno vinto il gioco.
    Il cavaliere che ha vinto il giro precedente salta un turno. 
    Usare semafori e variabili di condizione.
*/

armiere(){
    while(gioco_in_corso){
        // segnala ai cavalieri che sono arrivate tutte le spade
        signal(spade_posate)

        // aspetta i cavalieri che finiscono il turno 
        wait(fine_turno)
        
        // controllo se tutti hanno vinto
        wait(mutex)
        if(cavalieri_vincenti == N){
            signal(mutex)
            gioco_in_corso = 0
        }
    }
}

cavalieri(i){
    // aspetto che l'armiere posi le spade
    wait(spade_posate)

    // vado a decrementare la variabile delle spade in mutua esclusione
    wait(mutex)
    if(spade > 0 && spade <= M){
        spade --
        signal(mutex)
        
        // vado a segnalare che ho ottenuto una spada
        wait(mutex)
        spada_ottenuta ++
        // controllo se tutti hanno ottenuto una spada
        if(spade_ottenute == M)
            turno = true
            // segnalo a tutti i cavalieri che possono iniziare a giocare
            signal(inizio)
        signal(mutex)

        // aspetto che tutti siano pronti
        wait(inizio)

        // se tutti hanno preso la spada inizia il gioco
        while(turno){
            // peso la mia spada
            my_peso = pesa_spada()
            // verifico il peso della spada più grande 
            peso_vincente = max_peso()
            // se il peso coincide allora ho vinto
            if(my_peso == peso_vincente){
                // restituisco la spada
                wait(mutex)
                spade ++
                // incrermento il numero dei cavalieri vincenti
                cavalieri_vincenti ++
                signal(mutex)
                // esco perchè ho vinto
                exit()        
            }
            else{
                // poso la spada
                wait(mutex)
                spada ++
                signal(mutex)
            }
            // segnalo all'armiere che tutti hanno finito 
            signal(fine_turno)
            // segnalo che sono pronti per il prossimo turno
            signal(next_turn)
            // finisce il turno
            turno = false
            salta_turno(cavaliere(i))
        }
    }
    else{
        wait(next_turn)
        wait(spade_posate)

        // vado a segnalare che ho ottenuto una spada
        wait(mutex)
        spada_ottenuta ++
        // controllo se ogni cavaliere ha preso la spada per iniziare a giocarer
        if(spade_ottenute == M){
            turno = true
            signal(mutex)
            signal(tutti_pronti)
        }

        wait(tutti_pronti)

        // se tutti hanno preso la spada inizia il gioco
        while(turno){
            // peso la mia spada
            my_peso = pesa_spada()
            // verifico il peso della spada più grande 
            peso_vincente = max_peso()
            // se il peso coincide allora ho vinto
            if(my_peso == peso_vincente){
                // restituisco la spada
                wait(mutex)
                spade ++
                // incrermento il numero dei cavalieri vincenti
                cavalieri_vincenti ++
                signal(mutex)
                // esco perchè ho vinto
                exit()        
            }
            else{
                // poso la spada
                wait(mutex)
                spada ++
                signal(mutex)
            }
            // segnalo all'armiere che tutti hanno finito 
            signal(fine_turno)
            // segnalo che sono pronti per il prossimo turno
            signal(next_turn)
            //finisce il turno
            turno = false
            exit()
        }
    }
}