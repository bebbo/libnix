#include <errno.h>
#include <unistd.h>
#include "stdio.h"

int __fflush(FILE *stream);

int fseek(FILE *stream, long int offset, int whence) {
	__STDIO_LOCK(stream);

	if (stream->_flags & __SERR) /* Error on stream */
	{
		errno = EPERM;
		__STDIO_UNLOCK(stream);
		return EOF;
	}
	if (stream->_flags & __SWR)
		if (__fflush(stream)) {
			__STDIO_UNLOCK(stream);
			return EOF;
		}
	if (whence == SEEK_CUR)
		offset -= stream->_r + (stream->tmpp != NULL ? stream->tmpinc : 0);
	stream->_r = 0;
	stream->tmpp = NULL;
	stream->_flags &= ~(__SEOF | __SRD);
	if (lseek(stream->file, offset, whence) == EOF) {
		stream->_flags |= __SERR;
		__STDIO_UNLOCK(stream);
		return EOF;
	}
	__STDIO_UNLOCK(stream);
	return 0;
}
