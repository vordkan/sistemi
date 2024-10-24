#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 20;
int pid = 0;

int main ()
{
	int i;
	for (i = 2; i < 4; i ++)
	{
		pid = fork();
		if (pid == 0)
		{
			glob = glob * 2;
		}

		glob --;
	}

	printf ("Process %d, glob = %d \n", getpid(), glob);
}
