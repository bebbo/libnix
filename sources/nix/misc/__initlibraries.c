#include <proto/exec.h>
#include <proto/dos.h>
#include "stabs.h"
#include <string.h>

extern __far struct lib /* These are the elements pointed to by __LIB_LIST__ */
{
#ifdef __baserel__
	struct Library ** (*get)();
#define BASE *(*l->get)()
#else
	struct Library *base;
#define BASE l->base
#endif
	char const *name;
}

*__LIB_LIST__[];

extern __attribute__((noreturn)) void exit(int returncode);


static __attribute__((noreturn)) void __openliberror() {
	char buf[60];

	struct lib **list = __LIB_LIST__ + 1;
	struct lib * l;
	while ((l = *list++)) {
		if (BASE)
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
		if ((BASE = strstr(l->name, ".resource") ? OpenResource(l->name) : OldOpenLibrary(l->name)))
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
		struct Library *lb = BASE;
		if (lb != NULL) {
			if (!strstr(l->name, ".resource"))
				CloseLibrary(lb);
		}
	}
}

ADD2INIT(__initlibraries, -79);
ADD2EXIT(__exitlibraries, -79);
