/**
 * @file subprocess.c
 * @brief Writing a function that implements a version of Python’s subprocess.Popen functionality.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>

/**
 * @brief Run `cmdv[0]` with arguments `cmdv` in a child process.
 * 
 * @param cmdv a list containing the command to be run and its arguments.
 * 
 * @param pfd pipes opened between the parent and the child process.
 * Data written by the parent process to `pfd[0]` is read by the child's standard input.
 * Data written to child's standard output is read by the parent process via `pfd[1]`.
 * Data written to child's standard error is read by the parent process via `pfd[2]`.
 * 
 * @param envp a list of environment variables (passed to execve)
 * 
 * @return pid_t the process ID of the child or -1 on error.
 */
pid_t	subprocess(char* const cmdv[], char* const envp[], int pfd[3])
{
	pid_t	id;
	int		inpfd[2], outpfd[2], errpfd[2];

	if (pipe(inpfd) == -1 || pipe(outpfd) == -1 || pipe(errpfd) == -1) {
		goto error;
	}
	id = fork();
	if (id == -1) {
		goto error;
	}
	if (id == 0) {
		// Child process

		// clean up unused file descriptors
		close(inpfd[1]);
		close(outpfd[0]);
		close(errpfd[0]);

		// redirect child's io streams
		dup2(inpfd[0], STDIN_FILENO);
		dup2(outpfd[1], STDOUT_FILENO);
		dup2(errpfd[1], STDERR_FILENO);
		
		// printf("command-list: ");
		// for (int i = 0; cmdv[i]; i++) printf("%s ", cmdv[i]);
		// printf("\n");

		// execute the command
		int ret;
		ret = execve(cmdv[0], cmdv, envp);

		// exit
		close(inpfd[0]);
		close(outpfd[1]);
		close(errpfd[1]);
		if (ret == -1)
			exit(1);
		exit(0);
	}
	else {
		// Parent

		// handle redirections
		pfd[0] = inpfd[1];
		pfd[1] = outpfd[0];
		pfd[2] = errpfd[0];

		// clean up file descriptors
		close(inpfd[0]);
		close(outpfd[1]);
		close(errpfd[1]);

		// return process ID of the child
		return id;
	}
	error:
	if (inpfd[0] >= 0) {
		close(inpfd[0]);
		close(inpfd[1]);
	}
	if (outpfd[0] >= 0) {
		close(outpfd[0]);
		close(outpfd[1]);
	}
	if (errpfd[0] >= 0) {
		close(errpfd[0]);
		close(errpfd[1]);
	}
	return -1;
}

#define BUFFER_SIZE	64
int main(int ac, char **av, char **envp)
{
	/**
	 * Execute command passed in av in a subprocess
	 */
	if (ac == 1) {
		printf("./subprocess.out <command-list>\n");
		printf("example: ./subprocess.out /bin/ls -l -a\n");
		return 1;
	}

	// make a pipe
	int pfd[3] = {0};

	// execute command
	if (subprocess(av + 1, envp, pfd) == -1) {
		perror("subprocess");
		return 1;
	}

	// read subprocess's output stream
	char	buffer[BUFFER_SIZE + 1] = {0};
	int rret = 0;
	while ((rret = read(pfd[1], buffer, BUFFER_SIZE)) > 0) {
		// printf("%s", buffer);
		// bzero(buffer, BUFFER_SIZE + 1);
		write(1, buffer, rret);
	}
}