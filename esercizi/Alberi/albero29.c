#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int glob = 2, pid = 0, i;
    if(pid = fork()){
        glob ++;
        if(pid)
            fork();
    }

    for(i = 0; i < 1; i++){
        pid = fork();
        if(pid)
            glob *= 2;
        else   
            fork();
    }

    printf ("Process %d, glob = %d\n", getpid(), glob);
return 0;
}