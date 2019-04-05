
#define DEVICES_TIMER_H
#include <dos/dosextens.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include "stdio.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

/*
 **
 */
extern void __seterrno(void);

ssize_t read(int d, void *buf, size_t nbytes) {
	StdFileDes *sfd = _lx_fhfromfd(d);

	if (sfd) {
		long r;
		__chkabort();

		if (sfd->lx_fx)
			return sfd->lx_fx->lx_read(sfd, buf, nbytes);

		if ((r = Read(sfd->lx_fh, buf, nbytes)) != EOF)
			return r;
		__seterrno();
	}

	return EOF;
}
