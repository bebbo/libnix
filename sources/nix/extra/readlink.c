#include <proto/dos.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

 ssize_t readlink(const char *path, char *buf,  size_t bufsiz)
{
    struct DevProc *dp = NULL;
    BPTR lock = NULL;
    int retval = -1;

    lock = Open(path, MODE_OLDFILE);
    if (lock == NULL) {
	errno = ENOENT;
	goto done;
    }

    dp = GetDeviceProc(path, NULL);
    if (dp == NULL) {
	errno = EINVAL;
	goto done;
    }

    retval = ReadLink(dp->dvp_Port, lock, path, buf, bufsiz);
    if (retval == TRUE)
	retval = strlen(buf);
    else
	retval = -1;

done:
    if (dp != NULL)
	FreeDeviceProc(dp);
    
    if (lock != NULL)
	UnLock(lock);
    return retval;
}
