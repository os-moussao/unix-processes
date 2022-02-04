#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
	int fd = open("out.txt", O_CREAT | O_WRONLY, 0777);
	if (fd == -1) {
		perror("open");
	}
	if (dup2(fd, STDOUT_FILENO) == -1) {
		perror("dup2");
	}
	printf("This test sould now go to the file out.txt\n");
}