#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int glob=4;
int pid = 0;
int i=0;
int main(){
		printf("Sono %d figlio di %d. Glob: %d, Pid: %d\n\n",getpid(),getppid(),glob, pid);

	fork();
	glob--;
		printf("Sono %d figlio di %d. Glob: %d, Pid: %d\n\n",getpid(),getppid(),glob, pid);

	if (fork()){
		glob--;
			printf("Sono %d figlio di %d. Glob: %d, Pid: %d\n\n",getpid(),getppid(),glob, pid);

	}
	if (pid==0){
		for (i=1;i<2;i++){
			pid = fork();
			glob++;
				printf("Sono %d figlio di %d. Glob: %d, Pid: %d\n\n",getpid(),getppid(),glob, pid);

		}
	}
	if (pid==0)
		glob++;
			printf("Sono %d figlio di %d. Glob: %d, Pid: %d\n\n",getpid(),getppid(),glob, pid);

	if (!fork())
		printf("Sono %d figlio di %d. Glob: %d, Pid: %d\n\n",getpid(),getppid(),glob, pid);

		glob--;
}
