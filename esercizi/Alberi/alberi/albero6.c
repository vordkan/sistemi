#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int glob=0;
int main(){
	int i = 0;
	int pid = 0;
	pid= fork();
	if (pid!=0){	
		glob++;
		pid=fork();
		glob--;
		//printf("GLOB = %d\n",glob);
	}
	
	else if (pid==0){
		//printf("GLOB = %d\n",glob);
		for (i=1;i<=2;i++){
			pid = fork();
			glob++;
			//printf("GLOB = %d, i = %d\n",glob, i);
		}
	}
	glob--;	
		if (pid!=0)
		printf("PADRE.  Glob: %d, i: %d\n\n",glob, i);
	if (pid==0)
		printf("FIGLIO.  Glob: %d, i: %d\n\n",glob, i);
}
