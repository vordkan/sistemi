#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int glob = 5, pid = 0;
    fork();
    glob--;

   if(fork()){
    glob--;
   }

   if(pid == 0){
    pid = fork();
    glob--;
   }

    printf ("Process %d, glob = %d\n", getpid(), glob);

}