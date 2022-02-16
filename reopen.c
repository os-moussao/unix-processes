/**
 * @file reopen.c
 * @brief Reproducing the behavior of freopen(3)
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

/**
 * @brief a copy of freopen using file descriptors
 * 
 * @param path the targeted file pathname
 * @param oflags flags to be passed to open
 * @param permissions (rwx) permissions to the file - ignored if passed as -1
 * @param io_stream file descriptor of the stream ment to be redirected
 * 
 * @return file descriptor of the file opened or -1 on error
 */
int reopen(const char *path, int oflags, int permissions, int io_stream)
{
	if (close(io_stream) == -1) {
		return -1;
	}
	if (permissions != -1)
		return open(path, oflags, permissions);
	else
		return open(path, oflags);
}

int main()
{
	// save for backup
	int stdout_backup = dup(STDOUT_FILENO);

	int file = reopen("file.txt", O_RDWR | O_CREAT, 0777, STDOUT_FILENO);
	if (file == -1) {
		perror("reopen");
		return 1;
	}
	printf("Hello world to file.txt!\n");
	fflush(stdout);
	close(file);

	// backup
	dup2(stdout_backup, STDOUT_FILENO);
	printf("Hello world to STDOUT!\n");
}