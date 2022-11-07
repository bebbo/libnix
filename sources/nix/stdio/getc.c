#include "stdio.h"

int getc(FILE *stream) {
	int r;
	__STDIO_LOCK(stream);
	if (--stream->_r >= 0)
		r = *stream->_p++;
	else {
		// limit buffer size to 1 to read only one character.
		int sz = stream->_bf._size;
		stream->_bf._size = 1;
		r = __srget(stream);
		stream->_bf._size = sz;
	}
	__STDIO_UNLOCK(stream);
	return r;
}
