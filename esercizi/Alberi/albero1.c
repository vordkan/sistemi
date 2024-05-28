#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
	int glob = 5;
	int pid = 0;
	glob --;

	if (pid != 0)
	{
		pid = fork();
		glob --;
	}

	printf ("Process %d, valore di glob = %d\n", getpid(), glob);

	exit (0);
}
