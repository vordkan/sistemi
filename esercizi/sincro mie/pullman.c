/*
Un autobus è dotato di N posti a sedere ed M posti in piedi.
L'accesso dei passseggeri all'autobus avviene mediante 3 entrate.
Tutte le entrate posono esere utilizzate sia per salire che per scendere.
Si sale e si scende uno alla volta dando precedenza a chi scende su tutte le porte
*/

salita(){
    scelta_porta, scelta_posto : int
    mutex : mutex
    porta[2] : array 
    salita : semaforo binario

    while(true){
        // scelgo la porta di entrata
        scelta_porta = random(1,3)
        // in mutua esclusione controllo se la porta che ho scelto è libera
        lock(mutex)
        if(porta[scelta_porta] == 0){
            unlock(mutex)
            scelta_posto = rand(1,2)
            lock(mutex)
            // controllo se è il posto è a sedere ed è < N
            if(scelta_posto == 1 && posto[scelta_posto] < N){
                // decremento i posti disponibili a sedere 
                posto[scelta_posto] --
                unlock(mutex)
            }
            // controllo se è il posto in piedi ed è < M
            else if(scelta_posto == 2 && posto[scelta_posto] < M){
                // decremento i posti disponibili in piedi
                posto[scelta_posto] --
                unlock(mutex)
            }
            else{
                // se non ci sono i posti disponibili me ne vado a fanculo 
                unlock(mutex)
                exit()
            }
        }
        else{
            unlock(mutex)
            wait(salita)
            lock(mutex)
            // controllo se è il posto è a sedere ed è < N
            if(scelta_posto == 1 && posto[scelta_posto] < N){
                // decremento i posti disponibili a sedere 
                posto[scelta_posto] --
                unlock(mutex)
            }
            // controllo se è il posto in piedi ed è < M
            else if(scelta_posto == 2 && posto[scelta_posto] < M){
                // decremento i posti disponibili in piedi
                posto[scelta_posto] --
                unlock(mutex)
            }
            else{
                // se non ci sono i posti disponibili me ne vado a fanculo 
                unlock(mutex)
                exit()
            }
        }
    }
}

discesa(){
    while(true){
        lock(mutex)
        // mi recupero il posto dove ero seduto e poi lo libero
        if(my_posto == 1){
            posto[my_posto] ++
            unlock(posto)
            // scelgo la porta  
            scelta_porta = rand(1,3)
            // blocco la porta avendo la priorità per scendere
            lock(mutex)
            porta[scelta_porta] = 1
            unlock(mutex)
            scendo()
            lock(mutex)
            // libero la porta
            porta[scelta_porta] = 0
            unlock(mutex)
            // segnalo che possono salire ora
            signal(sali)
        }
        else{
            if(my_posto == 2){
                posto[my_posto] ++
                unlock(posto)
                // scelgo la porta  
                scelta_porta = rand(1,3)
                // blocco la porta avendo la priorità per scendere
                lock(mutex)
                porta[scelta_porta] = 1
                unlock(mutex)
                scendo()
                lock(mutex)
                // libero la porta
                porta[scelta_porta] = 0
                unlock(mutex)
                // segnalo che possono salire ora
                signal(sali)
            }
        }
    }
}