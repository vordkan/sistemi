/*
   I passeggeri in transito in un aeroporto prima di imbarcarsi sull' aereo devono superari i controlli di sicurezza.
   - ogni passeggero sceglie tra N code quella più breve a cui accodarsi ed attende il proprio turno per passare il controllo
   - ogni coda è gestita da un addetto che lascia passare il primo passeggero della coda, indirizzandolo verso una delle M code di accesso al metal detector.
     ogni addetto indirizza il passeggero verso la coda più breve con lunghezza < k 
   - se il numero di code con lunghezza < k è inferiore a M/2 gli addetti non lasciano passare i passeggeri finchè persiste tale condizione.
   dopo aver attrraversato il metal detector il passeggero si dirige all'imbarco
*/

passeggero(){
    while(true)
        // scelgo la coda più breve
        scelta = min(coda[N]) 

        lock(mutex)
        // incremento le persone in quella coda
        coda[scelta] ++       
        unlock(mutex)

        // segnalo che è arrirvato un passeggero in coda
        signal(passeggeri)  

        // aspetto che vengo chiamato dal controllore  
        wait(controllore)     
            
        lock(mutex)
        // decremento le persone di quella coda
        coda[scelta] --
        unlock(mutex)

        // aspetto che passo il controllo
        wait(metaldetector_passato) 

        exit()
    
    }
}

addetto(){
   while(true)
        // aspetto che arriva un passeggero
        wait(passeggeri)   

        // chiamo il primo della coda    
        signal(controllore)     

        coda_m = min(metaldetector[M])

        lock(mutex)
        // incremento le persone in coda del metaldetector
        metaldetector[coda_m] ++
        unlock(mutex)

        // aspetto che le code < k siano maggiori di M/2
        while(passato){                             
            lock(mutex)
            // mi conto quante sono le code minori di k
            minK = conta_minK(metaldetector[M])

            // le confronto se sono maggiori di M/2
            if(minK > M/2)
                unlock(mutex)

                // ora possono continuare i controlli
                signal(passato)
        }

        lock(mutex)
        // decremento le persone in coda del metaldetector
        metaldetector[coda_m] --
        unlock(mutex)

        // passa il controllo
        signal(metaldetector_passato) 
    }
}