#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUFSIZE 200

int main()
{
	int fd[2];
	int id;

	if (pipe(fd) == -1) {
		perror("Error with the pipe");
		exit(1);
	}
	id = fork();
	if (id == -1) {
		perror("Error opening the child");
		exit(2);
	}
	if (id == 0) {
		/* write something on the pipe from child process */
		write(fd[1], "Far far away, behind the word mountains, far from the countries \
Vokalia and Consonantia, there live the blind texts. Separated they live in Bookmarksgrove \
right at the coast of the Semantics, is large enough.", 199);
		close(fd[1]);
	}
	else {
		wait(NULL);
		char buf[BUFSIZE];
		if (read(fd[0], buf, BUFSIZE) >= BUFSIZE) {
			fprintf(stderr, "Buffer size of %d is not enough\n", BUFSIZE);
			exit(3);
		}
		printf("msg: %s\n", buf);
		close(fd[0]);
	}
}