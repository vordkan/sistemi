#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int glob=4;
int pid=0, j = 0;
int temp,i;
int main(){
	for (i=0;i<=2;i++){
		pid = fork();
		j++;
		glob++;
	}

	if (glob>5){
		glob++;
		if (pid==0){
			pid=fork();
			j++;
		}
		if (pid!=0){
			pid = fork();
			j++;
			glob--;
		}
		if (pid==0){
			pid = fork();
			j++;
			glob--;
		}
		if (pid!=0){
			temp=12;
			glob++;
			temp = glob;
			glob--;
		}
	}
	printf ("Process %d, glob = %d\n", j, glob);

}

