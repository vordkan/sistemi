/*
In una pizzeria, due pizzaioli sfornano continuamente pizze che pongono di volta in volta in uno di N piatti disponibili sul bancone.
i piatti sono prelevati da M<N camerieri che provvedono a servirle ai tavoli.
Ciascun cameriere può portare 2 pizze per volta se disponiili ma in caso di affollamento i camerieri prelevano 3 pizze per volta
*/

Pizzaioli(){
    while(true){
        // aspetto i piatti vuoti
        wait(piatto_empty)
        
        // metto le pizze nei piatti in mutua esclusione
        lock(mutex)
        for(i = 0 to N){
            piatto++
        }
        unlock(mutex)

        // segnalo che ci sono piatti pieni
        signal(piatto_full)   
    }

}

Camerieri(){
    while(true){
        // aspetto che ci sono piatti pieni
        wait(piatto_full)

        // in mutua esclusione mi controllo se c'è folla e servo i piatti
        lock(mutex)
        if(affollato == 1){
            for(i = 0 to 2){
                piatto--
                // se il piatto arriva a 0 allora segnalo al pizzaiolo che sforna altre pizze
                if(piatto == 0){
                    signal(piatto_empty)
                }
            }
            unlock(mutex)            
        }
        else{
            for(i = 0 to 1){
                piatto --
                if(piatto == 0){
                    signal(piatto_empty)
                }
            }
            unlock(mutex)
        }
    }
}