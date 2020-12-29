#include <errno.h>
#include <unistd.h>
#include "stdio.h"

long ftell(FILE *stream) {
	long pos;
	__STDIO_LOCK(stream);

	if (stream->_flags & __SERR) /* Error on stream */
	{
		errno = EPERM;
		__STDIO_UNLOCK(stream);
		return EOF;
	}
	if ((pos = lseek(stream->file, 0, SEEK_CUR)) == EOF) {
		stream->_flags |= __SERR;
		__STDIO_UNLOCK(stream);
		return pos;
	}
	if (stream->_flags & __SRD)
		pos -= stream->_r + (stream->tmpp != NULL ? stream->tmpinc : 0);
	else if (stream->_flags & __SWR)
		pos += stream->_p - stream->_bf._base;
	__STDIO_UNLOCK(stream);
	return pos;
}
