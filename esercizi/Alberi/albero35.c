#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 4;
int pid  = 4;
int var  = 4;
int main ()
{
    pid = fork();
    glob --;
    if(fork()){
        pid = fork();
        glob --;
        pid = 1;
    }
    if(!pid){
        glob --;
        var ++;
    }
    else{
        fork();
        glob ++;
        var --;
    }
    printf("valore di glob = %d, pid = %d, var = %d \n", glob,pid,var);
}
