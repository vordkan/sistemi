#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int glob = 5;
    int pid = 0;

    pid = fork();
    glob --;
    fork();
    glob --;
    pid = 1;

    if(!pid){
        glob --;
        fork();
    }

    printf ("Process %d, glob = %d\n", getpid(), glob);
    return 0;
}