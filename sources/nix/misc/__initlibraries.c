#include <proto/exec.h>
#include <proto/dos.h>
#include "stabs.h"
#include <string.h>

extern long __LIB_LIST__;

extern __attribute__((noreturn)) void exit(int returncode);

#pragma GCC push_options
#pragma GCC optimize ("-O2")

#define FAILED " failed to load\n"

static __attribute__((noreturn)) __attribute__((noinline)) void __openliberror() {
	char buf[80];

	long * l = &__LIB_LIST__ + 1;
	while (*l) {
		long * base = l++;
		char const * const name = *(char **) (l++);
		if (*base == -1) {
			strcpy(buf, name);
			strcat(buf, FAILED);
			Write(Output(), buf, strlen(buf));
		}
	}
	exit(20);
}

void __initlibraries(void) {
	long * l = &__LIB_LIST__ + 1;
	long failed = 0;
	while (*l) {
		long * base = l++;
		char const * const name = *(char **) (l++);
		long lib = (long)(strstr(name, ".resource") ? OpenResource(name) : OldOpenLibrary(name));
		if (lib)
			*base = lib;
		else
			failed = 1;
	}
	if (failed)
 		  __openliberror();
}

void __exitlibraries(void) {
	long * l = &__LIB_LIST__ + 1;
	while (*l) {
		long * base = l++;
		char const * const name = *(char **) (l++);
		if (*base != -1) {
			if (!strstr(name, ".resource"))
				CloseLibrary((struct Library *)*base);
		}
	}
}

#pragma GCC pop_options

ADD2INIT(__initlibraries, -79);
ADD2EXIT(__exitlibraries, -79);
