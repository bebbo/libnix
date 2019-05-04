#include <proto/exec.h>
#include <proto/dos.h>
#include "stabs.h"
#include <string.h>

extern struct lib /* These are the elements pointed to by __LIB_LIST__ */
{
	struct Library *base;
	char *name;
}*__LIB_LIST__[];

extern void exit(int returncode);


static __attribute__((noreturn)) void __openliberror() {
	char buf[60];

	struct lib **list = __LIB_LIST__ + 1;
	struct lib * l;
	while ((l = *list++)) {
		if (l->base)
			continue;
		strcpy(buf, l->name);
		strcat(buf, " failed to load\n");
		Write(Output(), buf, strlen(buf));
	}
	exit(20);
}

void __initlibraries(void) {
	struct lib **list = __LIB_LIST__ + 1;
	struct lib * l;
	short err = 0;
	while ((l = *list++)) {
		if ((l->base = OldOpenLibrary(l->name)))
			continue;
		err = 1;
	}
	if (err)
		__openliberror();
}

void __exitlibraries(void) {
	struct lib **list = __LIB_LIST__ + 1;
	struct lib * l;
	while ((l = *list++)) {
		struct Library *lb = l->base;
		if (lb != NULL) {
			CloseLibrary(lb);
		}
	}
}

ADD2INIT(__initlibraries, -60);
ADD2EXIT(__exitlibraries, -60);
