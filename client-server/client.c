#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

/**
 * Send number to server
 */


int main(int ac, char **av)
{
	if (ac != 3)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	int pid = atoi(av[1]);
	int data = atoi(av[2]);
	for (int i = 31; i >= 0; i--)
	{
		kill(pid, SIGUSR1 + ((data >> i) & 1));
		usleep(500);
	}
}
