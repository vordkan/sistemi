/*
    In un pub tedesco, due birrai riempiono continuamente boccali di birra che pongono di volta in volta in un bancone che può contenere N boccali.
    I boccali sono prelevati da M (M<N) camerieri che provvedono a servirle ai tavoli. 
    Ciascun cameriere può portare 2 boccali per volta, se disponibili, ma, in caso di affollamento, i camerieri preleveranno 4 boccali per volta. 
    Fornire una soluzione con semafori.
*/

birrai(){
    repeat
    {
        // aspetto che il bancone sia vuoto per produrre birra
        wait(bancone_vuoto)

        // riempio il boccale
        riempi()

        // ciclo sul bancone per vedere se non è pieno
        lock(mutex)
        for(i = 0 to N)
            if(bancone[i] == 0)
                bancone[i] = 1
                unlock(mutex)
                // segnalo che tutta la postazione è piena
                signal(bancone_pieno)
    }
    forever
}

cameriere(){
    repeat
    {
        // controllo se il locale è affollato
        affollato = rand(0,1)
        if(affollato == 1)
            // aspetto i boccali di birra
            wait(bancone_pieno)
            
            // vado in mutua escluione
            lock(mutex)

            // ciclo sul bancone per prendere 4 boccali
            for (i = 0 to 4)
                bancone[i] = 0
                unlock(mutex)
                // segnalo le birre finite
                signal(bancone_vuoto)
        else
             // aspetto i boccali di birra
            wait(bancone_pieno)
            
            // vado in mutua escluione
            lock(mutex)

            // ciclo sul bancone per prendere 4 boccali
            for (i = 0 to 2)
                bancone[i] = 0
                unlock(mutex)
                // segnalo le birre finite
                signal(bancone_vuoto)
    }
    forever
}

