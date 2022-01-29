#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 256

int main(int ac, char **av, char **env)
{
	char envar[BUFSIZE];

	if (ac != 2) {
		printf("./prog <var>\n");
		return 1;
	}
	if (!getenv(av[1])) {
		perror(av[1]);
		return 2;
	}
	if (snprintf(envar, BUFSIZE, "%s = %s", av[1], getenv(av[1])) >= BUFSIZE) {
		fprintf(stderr, "BUFFER SIZE %d too small\n", BUFSIZE);
	}
	printf("%s\n", envar);
}