#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/**
 * print nubmer recieved from client
 */

void h(int signal, siginfo_t *in, void *con)
{
	static int i;
	static int current_nbr;

	i++;
	current_nbr = (current_nbr << 1) | (signal & 1);
	if (i == 32) {
		printf("%d\n", current_nbr);
		i = 0;
		current_nbr = 0;
	}
}

int main()
{
	struct sigaction sa;
	sa.sa_sigaction = &h;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("%d\n", getpid());
	while (1);
}
