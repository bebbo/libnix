#include <proto/exec.h>
#include <proto/dos.h>
#include "stabs.h"
#include <string.h>

extern __far struct lib /* These are the elements pointed to by __LIB_LIST__ */
{
	struct Library *base;
	char const *name;
};

long __LIB_LIST__;

extern __attribute__((noreturn)) void exit(int returncode);


static __attribute__((noreturn)) void __openliberror() {
	char buf[60];

	int n = __LIB_LIST__ >> 1;
	struct lib * l = (struct lib *)(&__LIB_LIST__ + 1);
	while (n-- > 0) {
		if (!l->base) {
			strcpy(buf, l->name);
			strcat(buf, " failed to load\n");
			Write(Output(), buf, strlen(buf));
		}
		++l;
	}
	exit(20);
}

void __initlibraries(void) {
	int n = __LIB_LIST__ >> 1;
	struct lib * l = (struct lib *)(&__LIB_LIST__ + 1);
	short err = 0;
	while (n-- > 0) {
		if (!(l->base = strstr(l->name, ".resource") ? OpenResource(l->name) : OldOpenLibrary(l->name)))
			err = 1;
		++l;
	}
	if (err)
		__openliberror();
}

void __exitlibraries(void) {
	int n = __LIB_LIST__ >> 1;
	struct lib * l = (struct lib *)(&__LIB_LIST__ + 1);
	while (n-- > 0) {
		if (l->base != NULL) {
			if (!strstr(l->name, ".resource"))
				CloseLibrary(l->base);
		}
		++l;
	}
}

ADD2INIT(__initlibraries, -80);
ADD2EXIT(__exitlibraries, -80);
