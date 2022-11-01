#include <proto/exec.h>
#include <proto/dos.h>
#include "stabs.h"
#include <string.h>

extern long __LIB_LIST__;

extern __attribute__((noreturn)) void exit(int returncode);

#pragma GCC push_options
#pragma GCC optimize ("-O2")

static __attribute__((noreturn)) void __openliberror(char const * name) {
	char buf[80];

	strcpy(buf, name);
	strcat(buf, " failed to load\n");
	Write(Output(), buf, strlen(buf));
	exit(20);
}

void __initlibraries(void) {
	long * l = &__LIB_LIST__ + 1;
	while (*l) {
		long * base = l++;
		char const * const name = *(char **) (l++);
		*base = (long)(strstr(name, ".resource") ? OpenResource(name) : OldOpenLibrary(name));
		if (!*base) {
 		  __openliberror(name);
 		  break;
		}
	}
}

void __exitlibraries(void) {
	long * l = &__LIB_LIST__ + 1;
	while (*l) {
		long * base = l++;
		char const * const name = *(char **) (l++);
		if (!strstr(name, ".resource"))
			CloseLibrary((struct Library *)*base);
	}
}

#pragma GCC pop_options

ADD2INIT(__initlibraries, -79);
ADD2EXIT(__exitlibraries, -79);
