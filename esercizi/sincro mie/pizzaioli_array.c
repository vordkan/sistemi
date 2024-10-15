/*
In una pizzeria, due pizzaioli sfornano continuamente pizze che pongono di volta in volta in uno di N piatti disponibili sul bancone.
i piatti sono prelevati da M<N camerieri che provvedono a servirle ai tavoli.
Ciascun cameriere può portare 2 pizze per volta se disponiili ma in caso di affollamento i camerieri prelevano 3 pizze per volta
*/

pizzaioli(){
    while(true){
        // aspetto il piatto disponibile (piatto_empty)
        wait(piatto_empty)

        // sforno la pizza
        prepara()

        // inserisco le pizze preparate nei piatti 
        lock(mutex)
        for(i = 0 to N){
            piatto[i] = 1
        }
        unlock(mutex)

        // segnalo che c'è la pizza nel piatto (piatto_full)
        signal(piatto_full)
    }
}

cameriere(){
    while(true){
        // aspetto che ci sono piatti da servire
        wait(piatto_full)

        // controllo se il locale è affollato
        affollato = rand(0,1)

        lock(mutex)
        if(affollato == 1){

            // servo 3 piatti per volta e aumento i piatti disponibili 
            for(i = j to 2){
                piatti[i] = 0

                // controllo se sono finiti i piatti da servire
                if(j > N){
                    // se sono finiti lo segnalo e il pizzaiolo sforna altre pizze
                    signal(piatto_empty)
                }
                else{
                    // altrimenti proseguo a servire le pizze
                    j++
                }
            }
            unlock(mutex)
        }
        else{
            unlock(mutex)

            // servo 2 piatti per volta e aumento i piatti disponibili 
            for(i = j to 1){
                piatti[i] = 0

                // controllo se sono finiti i piatti da servire
                if(j > N){
                    // se sono finiti lo segnalo e il pizzaiolo sforna altre pizze
                    signal(piatto_empty)
                }
                else{
                    // altrimenti proseguo a servire le pizze
                    j++
                }
            }
            unlock(mutex)
        }
    }
}