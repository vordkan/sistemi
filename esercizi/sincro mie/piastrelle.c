/*
- In una fabbrica, N operai preparano piastrelle da far cuocere in un forno, capace di cuocerne M contemporaneamente.
- All'uscita dal forno K operai visionano le piastrelle per decorarle secondo tale sequenza di passi:
    + Se trova una piastrella difettata inizia a prenderne dal forno 2 alla volta
    + Altrimenti ne prende 1 alla volta
*/

opereai(){
    while(true){
        // aspetto che ci siano posti per infornare le piastrelle
        wait(forno_vuoto)

        // inforno gli ebrei gay
        inforna()

        // in mutua esclusione controllo gli spazzi liberi per mettere le piastrelle 
        for(i = 0 to M){
            lock(mutex)
            if(forno[i] == 0)
                forno[i] = 1
                unlock(mutex)
        }
        // segnalo che ci sono piastrelle che possono essere prelevate
        signal(forno_pieno)
    }
}

decoratori(){
    while(true){
        // aspetto che ci sono piastrelle che possono essere prelevate
        wait(forno_pieno)

        // ciclo su tutto il forno
        for(i = 0 to M){
            rotta = rand(0,1)
            lock(mutex)
            
            // controllo se è rotta
            if(rotta == 1){

                // parto dalla posizione della piastrella rotta e ne prelevo due 
                for(j = i to 1){
                    forno[j] = 0
                    unlock(mutex)  
                    
                    // segnalo che ci sono due posti vuoti
                    signal(forno_vuoto)              
                }
            }
            else{
                // altrimenti ne prendo solo una 
                forno[i] = 0
                unlock(mutex)
                // segnalo che c'è un posto disponibile
                signal(forno_vuoto)
            }
        }
    }
}
