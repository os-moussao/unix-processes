#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int ac, char **av, char **ev)
{
	int id = fork();
	if (id == -1) {
		return 1;
	}
	(void)ac;
	(void)av;
	if (id == 0) {
		// child
		printf("cpid = %d\n", getpid());

		// this is just to test with signals
		write(1, "Loading...", 10);
		for (int i = 0; i < 100; i++) {
			write(1, ".", 1);
			usleep(50000);
		}
		write(1, "\n", 1);

		// executing
		char *cav[] = {"/sbin/ping", "-c", "1", "google.com", NULL};
		int ret = execve("/sbin/ping", cav, ev);
		if (ret == -1) {
			perror("execve");
			return 1;
		}
	} else {
		// parent

		int ws;
		wait(&ws);

		write(1, "\n", 1);
		// child exited with an exit() call or with a return from the main function
		if (WIFEXITED(ws)) {
			int scode = WEXITSTATUS(ws);
			if (scode == 0) {
				printf("Child exited succesfully\n");
			} else {
				printf("Child exited with status code %d\n", scode);
			}
		}

		// child exited terminated by signal
		else if (WIFSIGNALED(ws)) {
			printf("Child was terminated by the signal %d\n",  WTERMSIG(ws));
		}

		// other
		else {
			printf("Child was stopped due to some error\n");
		}
		return 0;
	}
}