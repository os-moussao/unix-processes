#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int p[2];

	if (pipe(p) == -1) {
		fprintf(stderr, "Error\n");
		return 1;
	}
	int id = fork();
	if (id == -1) {
		fprintf(stderr, "Error\n");
		return 2;
	}
	if (id == 0) {
		// child process
		int x;

		if (read(p[0], &x, sizeof(x)) == -1) {
			return 3;
		}
		printf("Child recieves %d\n", x);
		x /= 2;
		sleep(3);
		if (write(p[1], &x, sizeof(x)) == -1) {
			return 4;
		}
		printf("Child sends %d\n", x);
		close(p[0]);
		close(p[1]);
	}
	else {
		// parent process
		int x;

		x = 42;
		sleep(3);
		if (write(p[1], &x, sizeof(x)) == -1) {
			return 4;
		}
		printf("Parent sends %d\n", x);
		if (read(p[0], &x, sizeof(x)) == -1) {
			return 3;
		}
		printf("Parent recieves %d\n", x);
		close(p[0]);
		close(p[1]);
	}
}