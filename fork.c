#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

// int main()
// {
// 	for (int i = 0; i < 5; i++) {
// 		fork();
// 	}
// 	printf("another process\n");
// }

int main()
{
	int id1 = fork();
	int id2 = fork();

	if (id1 == 0) {
		if (id2 == 0) {
			while (wait(NULL) != -1 && errno != ECHILD);
			printf("the child of the first child\n");
		}
		else {
			printf("the first child of the root process\n");
		}
	}
	else {
		if (id2 == 0) {
			printf("the second child of the root process\n");
		}
		else {
			while (wait(NULL) != -1 && errno != ECHILD);
			printf("the root process\n");
		}
	}
}