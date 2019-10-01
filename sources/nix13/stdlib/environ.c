#include <stdlib.h>
#include "stabs.h"
#include <exec/execbase.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <dos/dosextens.h>
#include <dos/var.h>

static char *dummy_env[] = { 0 };

char **environ;

int __fillenviron() {
	// size the environ
	environ = (char **)malloc(1 * sizeof(char *));
	if (environ == 0) {
		environ = dummy_env;
		errno = ENOMEM;
		return -1;
	}

	// fill the environ
	environ[0] = 0;
	return 0;
}

void __clearenviron() {
	if (environ != dummy_env) {
		char ** p = environ;
		while (*p) {
			free(*p++);
		}
		free(environ);
		environ = dummy_env;
	}
}

int clearenv(void) {
	__clearenviron();
	return 0;
}


ADD2INIT(__fillenviron,-2);
ADD2EXIT(__clearenviron,-2);
