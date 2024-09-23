#include <stdlib.h>
#include <string.h>
#include <dos/dos.h>
#include <dos/var.h>
#include <proto/dos.h>

#ifndef GVF_BINARY_VAR
#define GVF_BINARY_VAR 0x400
#endif

#ifdef __KICK13__
#include <exec/nodes.h>

#define LV_VAR 0
#define GVF_LOCAL_ONLY 0x200
struct LocalVar {
	struct Node lv_Node;
	UWORD	lv_Flags;
	UBYTE	*lv_Value;
	ULONG	lv_Len;
};
#endif

extern char **environ_ptr__data;

char *getenv(const char *name) {
	unsigned len;
	char **p;

	if (!name || !*name) {
		errno = EINVAL;
		return 0;
	}

	len = strlen(name);
	for (p = environ_ptr__data; *p; ++p) {
		if (0 == strncmp(*p, name, len) && len[*p] == '=')
			return len + 1 + *p;
	}

	if (0 == stricmp("HOME", name))
		return ("SYS:Prefs/Env-Archive");
	return 0;
}
