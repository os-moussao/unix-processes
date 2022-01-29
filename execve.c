#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	memmove(str, s1, len1);
	memmove(str + len1, s2, len2);
	str[len1 + len2] = 0;
	return (str);
}

int main()
{
	char PATH[BUFSIZE];
	char *var = "PATH";
	// char *tmp[] = {"test1", "test2", "test3", NULL};
	// execve("hello", tmp, NULL);

	if (!getenv(var)) {
		perror(var);
		return 1;
	}
	if (snprintf(PATH, BUFSIZE, "%s", getenv(var)) >= BUFSIZE) {
		fprintf(stderr, "BUFFER SIZE of %d is too small\n", BUFSIZE);
		return 2;
	}
	char d[] = ":";
	char *token;

	// printf("PATH = %s\n\n", PATH);

	token = strtok(PATH, d);
	while (token) {
		// printf("ith_path = %s\n", token);
		char *cmd;
		cmd = ft_strjoin(token, "/ls");
		// printf("%s\n", cmd);
		if (access(cmd, F_OK | X_OK) == 0) {
			printf("Executing Command: %s\n", cmd);
			char *av[] = {cmd, "-la", NULL};
			execve(cmd, av, NULL);
			return (0);
		}
		free(cmd);
		token = strtok(NULL, d);
	}
}