#include <stdlib.h>
#include <dos/dos.h>
#include <utility/tagitem.h>
#include <proto/dos.h>
#include <errno.h>
#include <string.h>
#include <stabs.h>

int system(const char *string) {
	if (string == NULL) {
		errno = EINVAL;
		return -1;
	}
#ifndef __KICK13__
	if (((struct Library *) DOSBase)->lib_Version >= 36) {
		static struct TagItem notags[] = { { TAG_END, 0 } };
		return SystemTagList((CONST_STRPTR )string, notags);
	} else
#endif
		return (int) ~Execute((STRPTR )string, 0l, Output());
}

int execv(const char *path, char * const argv[]) {
	int len = strlen(path) + 1;
	for (char * const * p = argv; *p; ++p) {
		len += 3 + strlen(*p);
	}
	char * cmd = malloc(len);
	strcpy(cmd, path);

	for (char * const * p = argv; *p; ++p) {
		strcat(cmd, " \"");
		strcat(cmd, *p);
		strcat(cmd, "\"");
	}

	int r = system(cmd);
	free(cmd);

	if (r >= 0)
		exit(0);
}

//int execvp(const char *file, char *const argv[]) {
//}

int pipe(int pipefd[2]) {
	return -1;
}

pid_t fork(void) {
	return 0;
}

ALIAS(execvp, execv);
