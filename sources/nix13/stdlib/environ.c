#include <stdlib.h>
#include "stabs.h"
#include <exec/execbase.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <dos/dosextens.h>
#include <dos/var.h>

static char *dummy_env[] = { 0 };

char ** environ_ptr__data = dummy_env;
char ***environ_ptr = &environ_ptr__data;

#undef environ
#define environ __dont_use_environ

int __fillenviron() {
	// not yet implemented
	return 0;
}

int clearenv(void) {
	if (environ_ptr__data != dummy_env) {
		char ** p = environ_ptr__data;
		while (*p) {
			free(*p++);
		}
		free(environ_ptr__data);
		environ_ptr__data = dummy_env;
	}
	return 0;
}


ADD2INIT(__fillenviron,-2);
