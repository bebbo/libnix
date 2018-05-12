#include <stdlib.h>
#include <string.h>
#include <dos/var.h>
#include <proto/dos.h>

#ifndef GVF_LOCAL_ONLY
#define GVF_LOCAL_ONLY 0x200
#endif

int setenv(const char *name, const char *value, int overwrite) {
    char *old = getenv(name);
    int retval = 0;
    if (old == NULL || overwrite) {
		retval = SetVar(name, value, strlen(value), GVF_LOCAL_ONLY) == TRUE ? 0 : -1;
    }
    return retval;
}

int unsetenv(const char *name) {
    return -!DeleteVar(name, GVF_LOCAL_ONLY);
}
int putenv(const char *str) {
    char *tmp = malloc(strlen(str) + 1);
    int retval = -1;
    char *pos;
    if (tmp == NULL) {
        goto end;
    }
    strcpy(tmp, str);
    pos = strchr(tmp, '=');
    if (pos == NULL)
        goto end;
    *pos++ = '\0';

    retval = setenv(str, pos, 1);

end:
    if (tmp != NULL)
        free(tmp);
    return retval;
}

