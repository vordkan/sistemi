/*
    Il chitarrista Mancuso ha una mastercass in cui possono prendere parte N chitarristi, che possono scegliere tra
    M modelli di chitarre con k chitarre per modello.

    Quando tutti gli allievi hanno una chitarra, inizia il masterclass. 
    Quelli che non trovano posto prenderanno parte alla lezione successiva. 
    Tutto termina quando non ci sono chitarristi in attesa
*/

chitarristi(){
    int modello, chitarra;
    int** chitarre;
    mutex: mutex;
    chitarra_ottenuta, inizio_lezione, fine_lezione, prossima_lezione: semaforo binario;
    posto_disponiile, in_attesa: semaforo contatore;


    // vado in mutua esclusione perchè devo accedere alla variabile delle chitarre e poi la vado a decrementare
    lock(mutex)
        modello = scelgo_modello() 
        chitarra = scelgo_chitarra()
        chitarre[modello][chitarra] -- 
    unlock(mutex)

    // avviso al maestro che ho ottenuto la chitarra
    signal(chitarra_ottenuta)

    // vado in mutua esclusione per controllare i posti se sono disponibili, se ci sono posso sedermi 
    // e fare la lezione, altrimenti aspetto la lezione successiva.
    lock(mutex)
        if(posto_disponibile > 0){
            unlock(mutex)

            wait(posto_disponibile)   // lo decremento perchè significa che ho preso posto
            wait(inizio_lezione)      // aspetto l'inizio della lezione 
            wait(fine_lezione)        // aspetto che la lezione finisca
            signal(posto_disponibile) // mi alzo dal posto e incremento la variabile
        }
        
        else{
            unlock(mutex)
            signal(in_attesa)         // avverto al maestro che ci sono allievi per la prossima lezione
            wait(prossima_lezione)    // aspetto che il maestro faccia la prossima lezione
            wait(posto_disponibile)   // decremento la variabile del posto disponibile
            wait(inizio_lezione)      // attendo che la lezione inizia
            wait(fine_lezione)        // attendo che la lezione finisca
            signal(posto_disponibile) // mi alzo incremento la varibile dei posti disponibili
            wait(in_attesa)           // decrermento la variabile dei posti in attesa 
        }
}


maestro(){
    wait(chitarra_ottenuta); // aspetto che tutti hanno una chitarra

    // controlliamo se ci sono persone sedute e iniziamo la lezione. Altrimenti la lezione è conclusa
    lock(mutex)
    if(posti_disponibili > 0){ // vuol dire che ci sono persone in attesa di fare la lezione
        unlock(mutex)
        signal(inizio_lezione) 
        fai_lezione()
        signal(fine_lezione)  // avverto agli studenti che la lezione è finita e possono alzarsi

        lock(mutex)
        if(in_attesa > 0){             // ora passo al turno delle persone che stavano aspettando per la prossima lezione
            unlock(mutex)
            wait(in_attesa)            // mi decremento la variabile delle persone in attesa
            signal(inizio_lezione)      
            fai_lezione()
            signal(fine_lezione)
        }
        else{
            unlock(mutex)
             exit() // se non ci sono persone allora la lezione è finita
        }
    } 
    else{
        unlock(mutex)
        exit()
    }
} 