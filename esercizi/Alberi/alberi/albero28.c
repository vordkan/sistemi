#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 8;
int pid = 0;
int i;
int main(){
    for(i = 2; i <=glob; i++){
        pid = fork();
        if(pid == 0){
            glob = glob -2;
        }
        glob --;
    }
    printf ("Process %d, glob = %d\n", getpid(), glob);
    return 0;
}