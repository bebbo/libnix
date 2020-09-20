#include <stdlib.h>
#include <string.h>
#include <dos/var.h>
#include <proto/dos.h>

#ifndef GVF_LOCAL_ONLY
#define GVF_LOCAL_ONLY 0x200
#endif

extern int __clearenviron();
extern int __fillenviron();

int setenv(const char *name, const char *value, int overwrite) {
	if (name && *name) {
		char *old = getenv(name);
		if (old == NULL || overwrite) {
			if (SetVar((CONST_STRPTR )name, (CONST_STRPTR )value, strlen(value) + 1, GVF_LOCAL_ONLY)) {
				__clearenviron();
				__fillenviron();
			}
		}
		return 0;
	}
	errno = EINVAL;
	return -1;
}

int putenv(const char *str) {
	int retval = -1;
	if (str && *str) {
		char *tmp = malloc(strlen(str) + 1);
		if (!tmp) {
			errno = ENOMEM;
		} else {
			char * pos;

			strcpy(tmp, str);
			pos = strchr(tmp, '=');
			if (pos) {
				*pos++ = '\0';
				retval = setenv(tmp, pos, 1);
			} else
				errno = EINVAL;
			free(tmp);
		}
	} else
		errno = EINVAL;
	return retval;
}

