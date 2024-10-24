#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 0;
int pid = 0;

int main ()
{
    while(!fork()){
        glob += 2;
        if(pid > 0){
            glob ++;
        }
        else{
            pid = fork();
            glob ++
        }
        if(glob > 5){
            exit(1);
        }
    }
    printf("glob = %d \n", glob);
}
