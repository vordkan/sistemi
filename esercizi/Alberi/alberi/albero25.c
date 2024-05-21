#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int glob = 0, pid = 0, i;
    pid = fork();

    if(pid == 0){
        glob ++;
        fork();
    }

    for(i = 0; i <= glob; i++){
        if(pid)
            fork();
        if(!pid)
            pid = fork();
    }

    printf ("Process %d, glob = %d\n", getpid(), glob);

}