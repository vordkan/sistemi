#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 8;
int pid = 0;

int main ()
{
	int i;
	for (i = 2; i <= glob; i ++)
	{
		pid = fork();
		if (pid == 0)
		{
			glob = glob - 2;
		}

		glob --;
	}

	printf ("Process %d, glob = %d i = %d\n", getpid(), glob, i);
}
