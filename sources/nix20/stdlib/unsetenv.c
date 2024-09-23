#include <stdlib.h>
#include <string.h>
#include <dos/var.h>
#include <proto/dos.h>

#undef environ
#define environ __dont_use_environ

int unsetenv(const char *name) {
	if (name && *name) {
		return setenv(name, 0, 1);
    }
	errno = EINVAL;
    return -1;
}
