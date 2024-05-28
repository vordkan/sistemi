#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
    int glob = 6;
    int pid = 0;
    while(!pid){
        if(!fork()){
            glob -= 3;
        }
        else{
            glob--;
            if((pid = fork()) == 0){
                pid = 1;
                fork();
                glob--;
            }
        }
            
        if(glob == 0) {
            pid = 10;
        }
    }

    printf("glob %d\n",glob);
    return 0;
}