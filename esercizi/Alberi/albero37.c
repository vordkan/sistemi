#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 0;
int pid = 0;

int main ()
{
    while(!fork()){
        glob ++;
        if(fork()){
            pid = 1;
        }
        else{
            fork();
            glob ++
        }
        if(glob > 1){
            exit(1);
        }
    }
    printf("glob = %d \n", glob);
}
