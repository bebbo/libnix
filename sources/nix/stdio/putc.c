#include "stdio.h"

int putc(int c, FILE *stream) {
	int r;
	__STDIO_LOCK(stream);

	if (--stream->_w >= 0 || (stream->_w >= stream->linebufsize && (char) (c) != '\n'))
		r = *stream->_p++ = c;
	else
		r = __swbuf(c, stream);
	__STDIO_UNLOCK(stream);
	return r;
}
