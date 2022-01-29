#include <stdio.h>

int main(int ac, char **av)
{
	while (ac--) {
		printf("arg = %s\n", av[ac]);
	}
	printf("bye from command\n");
}