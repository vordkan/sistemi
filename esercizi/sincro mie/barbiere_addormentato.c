/*
Quando arriva, un cliente sveglia il barbiere e si fa tagliare i capelli sulla poltrona
Se arriva un cliente mentre il barbiere sta tagliando i capelli ad un altro
cliente, il cliente attende su una delle sedie libere
Se tutte le sedie sono occupate, il cliente, contrariato, se ne va!
*/

Barbiere(){
    while(true){
        // aspetto di essere svegliato
        wait(sveglia)
        
        // segnalo che può procedere al taglio
        signal(taglio)

        taglia_capelli()
        
        // fine taglio
        signal(fine_taglio)
    }
}

Cliente(){
    // controllo se ci sono sedie disponibili in mutua esclusione
    lock(mutex)
    if(sedie == 0){
        unlock(mutex)   
        // me ne esco contrariato 
        exit()
    }
    else{
        // decremento le sedie disponibili
        sedie --
        unlock(mutex)

        // sveglio il barbiere
        signal(sveglia)

        // aspetto di essere chiamato al taglio
        wait(taglio)

        // mi alzo e libero una sedia
        lock(mutex)
        sedie ++
        unlock(mutex)

        // aspetto la fine del taglio per uscire
        wait(fine_taglio)
        exit()
    }
}