#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


int main(int ac, char **av)
{
	if (ac != 2) {
		return 1;
	}
	DIR	*dir;
	struct dirent *p;
	dir = opendir(av[1]);
	if (!dir) {
		perror(av[1]);
		return 2;
	}
	while ((p = readdir(dir))) {
		printf("%-30s	type: %s\n", p->d_name, p->d_type == DT_DIR? "directory": "file");
	}
	closedir(dir);
}
