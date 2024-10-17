/* In un sistema sono attivi N processi dotati di un credito C.
   Ogni processo genera un numero casuale P in [1...C] e verifica se il proprio P è
   maggiore di quello degli altri processi (a parità di P vince il processo con il PID minore).
   Il processo vincitore (quello con P maggiore) aggiunge al proprio credito C le quantità
   P generate da tutti gli altri processi, che invece sottraggono al proprio credito C la 
   quantità P generata.
   Un processo con credito C=0 termina
*/

processo(i){
    // il processo(i) controlla se ha il credito maggiore di 0
    while(credito[i] > 0){
        // genera un numero
        numero_generato = rand(1, credito)
        // lo associa alla sua posizione
        P[i] = numero_generato

        wait(barrier)
        // controlla se il numero è il maggiore di tutti gli altri 
        if(numero_generato == max(P)){
            for(j = 0 to N){
                if(i == j){
                    credito[j] += P[j]
                }
            }
            signal(barrier)
        }
        else{
            for(j = 0 to N){
                if(i != j){+
                    credito[j] -= P[j]
                }
            }
            signal(barrier)
        }
    // esce se non ha credito sufficiente 
    exit()
    }
}
