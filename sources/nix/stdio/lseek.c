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

off_t lseek(int d, off_t offset, int whence) {
	StdFileDes *sfd = _lx_fhfromfd(d);

	if (sfd) {
		long r, file = sfd->lx_fh;
		__chkabort();
		if (Seek(file,offset,whence==SEEK_SET?OFFSET_BEGINNING:
				whence==SEEK_END?OFFSET_END:OFFSET_CURRENT) != EOF)
			if ((r = Seek(file, 0, OFFSET_CURRENT)) != EOF)
				return r;
		__seterrno();
	}

	return EOF;
}
