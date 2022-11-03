#include <dos/dosextens.h>
#include <proto/dos.h>

#include <sys/types.h>
#include <sys/stat.h>
#include "string.h"
#include "stdio.h"


int fstat(int d,struct stat *buf) {
	if (!buf)
		return -1;

	memset(buf, 0, sizeof(*buf));

	off_t here = lseek(d, 0, OFFSET_CURRENT);
	if (here == -1) {
		buf->st_mode = 0777 | _IFDIR;
		return 0;
	}

	buf->st_mode = 0777 | _IFREG | _IFCHR;
	buf->st_size = lseek(d, 0, OFFSET_END);
	buf->st_blksize = 512;
	buf->st_blocks = (buf->st_size + 511)/ 512;

	lseek(d, here, OFFSET_BEGINNING);

	return 0;
}
