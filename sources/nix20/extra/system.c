#include <stdlib.h>
#include <dos/dos.h>
#include <utility/tagitem.h>
#include <proto/dos.h>
#include <errno.h>
#include <string.h>

int system(const char *string) {
	if (string == NULL) {
		errno = EINVAL;
		return -1;
	}
#ifndef __KICK13__
	if (((struct Library*) DOSBase)->lib_Version >= 36) {
		static struct TagItem notags[] = { { TAG_END, 0 } };
		return SystemTagList((CONST_STRPTR )string, notags);
	} else
#endif
		return (int) ~Execute((STRPTR )string, Input(), Output());
}
#if 0
int execvp(const char *file, char *const argv[]) {
	return execv(file, argv);
}
#endif
asm("_execvp: .globl _execvp\n");
int execv(const char *path, char *const argv[]) {
	char *const*p;
	char *cmd;

	int len = 1 + strlen(path);
	for (p = argv; *p; ++p) {
		len += 3 + strlen(*p);
	}
	cmd = malloc(len);
	strcpy(cmd, path);

	if (*argv)
	for (p = argv+1; *p; ++p) {
		strcat(cmd, " \"");
		strcat(cmd, *p);
		strcat(cmd, "\"");
	}
	return system(cmd);
}

int execve(const char *path, char *const argv[], char *const envp[]) {
	return execv(path, argv);
}

int pipe(int pipefd[2]) {
	return -1;
}

pid_t fork(void) {
	return 0;
}
