#include <stdlib.h>
#include <string.h>
#include <dos/var.h>
#include <proto/dos.h>

extern int __clearenviron();
extern int __fillenviron();

int unsetenv(const char *name) {
	if (name && *name && DeleteVar(name, 0)) {
    	__clearenviron();
    	__fillenviron();
    	return 0;
    }
	errno = EINVAL;
    return -1;
}
