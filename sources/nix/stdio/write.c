#include "stdio.h"

#include <dos/dosextens.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

/*
 **
 */
extern void __seterrno(void);

ssize_t write(int d, const void *buf, size_t nbytes) {
	StdFileDes *sfd = _lx_fhfromfd(d);

	if (sfd) {
		long r;
		__chkabort();

		if (sfd->lx_fx)
			return sfd->lx_fx->lx_write(sfd, buf, nbytes);

		do { // while (0);
			if ((sfd->lx_oflags & O_APPEND) != 0) {
				if (!(sfd->lx_flags & LX_ATTY) && (Seek(sfd->lx_fh,0,OFFSET_END) == EOF))
					break;
			}
			if ((r = Write(sfd->lx_fh, (char * )buf, nbytes)) != EOF)
				return r;
		} while (0);
		__seterrno();
	}

	return EOF;
}

