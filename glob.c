/**
 * @brief using glob function for pattern matching
 */

#include <glob.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	errfunc(const char *epath, int eerrno)
{
	fprintf(stderr, "glob: %s: %s\n", epath, strerror(eerrno));
	fflush(stderr);
	return 1;
	// return 0;
}

int	glob_check_error(int ret)
{
	if (ret == GLOB_NOSPACE) {
		fprintf(stderr, "glob: running out of memory!\n");
		fflush(stderr);
	}
	else if (ret == GLOB_ABORTED) {
		fprintf(stderr, "glob: a read error has occured!\n");
		fflush(stderr);	
	}
	else if (ret == GLOB_NOMATCH) {
		fprintf(stderr, "glob: no matches found!\n");
		fflush(stderr);
	}
	return ret;
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	glob_t	glob_buff;
	int		ret;

	glob_buff.gl_pathc = 0;
	glob_buff.gl_pathv = NULL;
	glob_buff.gl_offs = 2;
	ret = glob("~/Desktop/*.html", GLOB_DOOFFS | GLOB_TILDE | GLOB_NOSORT, &errfunc, &glob_buff);

	// Testing errfunc and glob_check_error:
	// ret = glob("/usr/bin/wrapper.app/*", GLOB_DOOFFS | GLOB_TILDE | GLOB_NOSORT, &errfunc, &glob_buff);
	
	glob_check_error(ret);

	glob_buff.gl_pathv[0] = "/bin/ls";
	glob_buff.gl_pathv[1] = "-l";

	ret = glob("../minishell/src/*/*.c", GLOB_DOOFFS | GLOB_TILDE | GLOB_NOSORT | GLOB_APPEND, &errfunc, &glob_buff);
	glob_check_error(ret);

	execve(glob_buff.gl_pathv[0], glob_buff.gl_pathv, envp);
}