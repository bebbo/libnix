#define DEVICES_TIMER_H
#include <dos/dosextens.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdio.h>
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
		switch ((sfd->lx_oflags & O_APPEND) != 0) {
		case 1:
			if (!sfd->lx_isatty && (Seek(sfd->lx_fh,0,OFFSET_END) == EOF))
				break;
		default:
			if ((r = Write(sfd->lx_fh, (char * )buf, nbytes)) != EOF)
				return r;
		}
		__seterrno();
	}

	return EOF;
}

