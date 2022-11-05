#include <proto/dos.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

ssize_t readlink(const char *path, char *buf, size_t bufsiz) {
	struct DevProc *dp = NULL;
	BPTR lock = 0;
	int retval = -1;

	lock = Open((CONST_STRPTR)path, MODE_OLDFILE);
	if (lock == 0) {
		errno = ENOENT;
		goto done;
	}

	dp = GetDeviceProc((CONST_STRPTR)path, NULL);
	if (dp == NULL) {
		errno = EINVAL;
		goto done;
	}

	retval = ReadLink(dp->dvp_Port, lock, (CONST_STRPTR)path, (STRPTR)buf, bufsiz);
	if (retval == TRUE)
		retval = strlen(buf);
	else
		retval = -1;

	done: if (dp != NULL)
		FreeDeviceProc(dp);

	if (lock != 0)
		UnLock(lock);
	return retval;
}
