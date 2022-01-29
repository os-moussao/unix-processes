#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	struct stat stat;
	lstat("./hello.c", &stat);
	printf("size  of hello.c is %lu bytes\n", stat.st_size);
}