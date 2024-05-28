#include <unistd.h>
#include <stdio.h>

int main(){
    int g = 5;
    int p = 0;

    p = fork();
    g--;

    fork();
        
    if(p > 0){

        p = fork();
        g--;
    }

   printf ("Process %d, glob = %d\n", getpid(), g);

}