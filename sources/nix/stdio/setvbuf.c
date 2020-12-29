#include <errno.h>
#include <stdlib.h>
#include "stdio.h"

int __fflush(FILE *stream);

int setvbuf(FILE *stream, char *buf, int mode, size_t size) {
	__STDIO_LOCK(stream);

	short flags = stream->_flags & ~(__SNBF | __SLBF);
	if (mode == _IONBF)
		flags |= __SNBF;
	else if (mode == _IOLBF)
		flags |= __SLBF;
	if (size != (size_t) stream->_bf._size || buf != (char *) stream->_bf._base) {
		if (__fflush(stream)) {
			__STDIO_UNLOCK(stream);

			return -1;
		}
		stream->_r = 0;
		stream->_flags = (flags &= ~(__SRD|__SWR));
		stream->tmpp = 0;
		mode = (buf == NULL);
		if (mode && (buf = malloc(size = size ? size : 1)) == NULL) {
			errno = ENOMEM;

			__STDIO_UNLOCK(stream);
			return -1;
		}
		if (flags & __SMBF)
			free(stream->_bf._base);
		if (mode)
			flags |= __SMBF;
		else
			flags &= ~__SMBF;
		stream->_bf._base = (unsigned char *) buf;
		stream->_bf._size = size;
	} /* Need not adjust outcount, since setvbuf affects only the NEXT full buffer */
	stream->_flags = flags;

	__STDIO_UNLOCK(stream);
	return 0;
}
