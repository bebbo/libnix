#include <proto/exec.h>
#include <proto/dos.h>
#include "stabs.h"
#include <string.h>

struct lib /* These are the elements pointed to by __LIB_LIST__ */
{
	struct Library *base;
	char *name;
}*__LIB_LIST__[] = {0};

extern void exit(int returncode);


static __attribute__((noreturn)) void __openliberror(ULONG version, char const * ln) {
	char buf[60];
	strcpy(buf, ln);
	strcat(buf, " failed\n");
	Write(Output(), buf, strlen(buf));
	exit(20);
}

void __initlibraries(void) {
	struct lib **list = __LIB_LIST__ + 1;
	struct lib * l;
	while ((l = *list++)) {
		if ((l->base = OpenLibrary(l->name, 0)) == NULL)
			__openliberror(0, l->name);
	}
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
