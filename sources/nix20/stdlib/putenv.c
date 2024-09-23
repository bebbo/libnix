#include <stdlib.h>
#include <string.h>
#include <dos/var.h>
#include <proto/dos.h>

#ifndef GVF_LOCAL_ONLY
#define GVF_LOCAL_ONLY 0x200
#endif

extern char ** environ_ptr__data;
extern char *__dummy_env[];

int setenv(const char *name, const char *value, int overwrite) {
	if (name && *name && value && !strchr(name, '=')) {

		int l = strlen(name);
		char ** p = environ_ptr__data;
		while (*p) {
			char * v = *p;
			if (0 == strncmp(v, name, l) && v[l] == '=') {
				// found
				if (!overwrite) // do nothing
					return 0;

				free(v);
				if (!*value) { // remove
					for (char **q = p + 1; ;) {
						if (!(*p++ = *q++))
							return 0;
					}
				}
				// replace
				*p = concat(name, "=", value, 0);
				return 0;
			}
			++p;
		}
		// insert
		char ** neu;
		if (environ_ptr__data != __dummy_env)
			neu = (char **)realloc(environ_ptr__data, (p - environ_ptr__data + 1) * sizeof(char *));
		else
			neu = (char **)malloc(2 * sizeof(char *));

		if (!neu)
			return ENOMEM;

		if (environ_ptr__data != __dummy_env)
			p = neu + (p - environ_ptr__data);
		else
			p = neu;

		*p++ = concat(name, "=", value, 0);
		*p = 0;
		return 0;
	}
	errno = EINVAL;
	return -1;
}

int putenv(const char *str) {
	int retval = -1;
	if (str && *str) {
		char *tmp = strdup(str);
		if (!tmp) {
			errno = ENOMEM;
		} else {
			char * pos;
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

