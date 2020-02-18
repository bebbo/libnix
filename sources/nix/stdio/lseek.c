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

	if (sfd) {
		off_t r;
		int file = sfd->lx_fh;

		// seek ...
		r = Seek(file, offset, whence == SEEK_SET ? OFFSET_BEGINNING : whence == SEEK_END ? OFFSET_END : OFFSET_CURRENT);

		// seek failed - check if it would extend the file
		if (r == EOF && sfd->lx_oflags) {
			// to support a seek behind file end to extend the file it's necessary to know the resulting position.
			off_t abs_pos = offset;

			// determine the resulting seek position
			if (whence == SEEK_CUR) {
				r = Seek(file, 0, OFFSET_CURRENT);
				abs_pos += r;
			} else if (whence == SEEK_END) {
				if (whence <= 0)
					r = EOF;
				else {
					Seek(file, 0, OFFSET_END);
					r = Seek(file, 0, OFFSET_END);
					abs_pos += r;
				}
			} else { // SEEK_SET
				r = 0;
			}

			// if not at end yet - seek
			if (r != EOF && whence != SEEK_END) {
				Seek(file, 0, OFFSET_END);
				r = Seek(file, 0, OFFSET_END);
			}

			// still ok?
			if (r != EOF && abs_pos > r) {
				// if the file is too small
				// extend the file to reach that offset.
				static char *tmp;
				unsigned sz = 0x1000;
				if (!tmp)
					tmp = malloc(sz);

				// note that SetFileSize does not always work
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
