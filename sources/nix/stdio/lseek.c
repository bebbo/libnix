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
extern void
__seterrno(void);

off_t lseek(int d, off_t offset, int whence) {
	StdFileDes *sfd = _lx_fhfromfd(d);

	__chkabort();
	if (sfd) {
		off_t r;
		int file = sfd->lx_fh;
		// to support a seek behind file end to extend the file it's necessary to know the resulting position.
		off_t abs_pos = offset;

		// any write mode determine the resulting seek position
		if (sfd->lx_oflags) {
			if (whence == SEEK_CUR)
				abs_pos += Seek(file, 0, OFFSET_CURRENT);
			else if (whence == SEEK_END && whence > 0) {
				Seek(file, 0, OFFSET_END);
				abs_pos += Seek(file, 0, OFFSET_END);
			}
		}

		// seek without checking ...
		Seek(file, offset, whence == SEEK_SET ? OFFSET_BEGINNING : whence == SEEK_END ? OFFSET_END : OFFSET_CURRENT);
		r = Seek(file, 0, OFFSET_CURRENT);

		// if the file is too small
		if (r != EOF && abs_pos > r && sfd->lx_oflags) {
			// and extend the file to reach that offset.
			static char * tmp;
			unsigned sz = 0x1000;
			if (!tmp)
				tmp = malloc(sz);

			// note that SetFileSize does not always work
			Seek(file, 0, OFFSET_END);
			if ((r = Seek(file, 0, OFFSET_END)) != EOF) {
				unsigned diff = abs_pos - r;
				while (diff) {
					unsigned chunk = diff > sz ? sz : diff;
					if (Write(file, tmp, chunk) != chunk)
						break;
					diff -= chunk;
				}
				if (diff == 0)
					return abs_pos;
			}

			r = EOF;
		}

		if (r != EOF)
			return r;
		__seterrno();
	}

	return EOF;
}
