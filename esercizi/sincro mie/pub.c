/*
Un gruppo di amici festeggia in un pub con B bottiglie di birra.
Il garzone del pub aggiunge una bottiglia di birra ogni volta che riscontra personalmente che una bottiglia è vuota.
Egli agisce in modo prioritario rispetto gli amici.
Gli amici hanno concordato di accedere alle B bottiglie di birra per non più di M volte consecutive ciascuno, 
tra due consecutive sostituzioni di bottiglia effettuate dal garrzone.
*/

Garzone{
    while(true){
        // aspetto ci siano bottiglie vuote
        wait(bottiglia_empty)

        // in mutua esclusione aggiungo le bottiglie
        lock(mutex)
        bottiglia ++
        unlock(mutex)

        // dico che possono bere 
        signal(bottiglia_full)
    }
}

Amici(){
    // controllo in mutua esclusione se ho fatto meno di M accessi
    lock(mutex)
    if(accesso < M){
        accesso ++
        unlock(mutex)
        
        //controllo in mutua esclusione se ho fatto meno di due accessi consecutivi
        lock(mutex)
        if(consecutive < 2){
            
            // incremento le consecutive
            consecutive ++
            unlock(mutex)

            // aspetto che ci sono bottiglie da poter bere
            wait(bottiglia_full)

            // decremento le bottiglie in mutua esclusione
            lock(mutex)
            bottiglia--
            unlock(mutex)

            // segnalo che è vuota per farla riempire
            signal(bottiglia_empty)
        }
        else{
            unlock(mutex)
            exit()
        }
    }
    else{
        unlock(mutex)
        exit()
    }
}