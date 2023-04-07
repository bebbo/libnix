#include "stdio.h"

int getc(FILE *stream) {
	int r;
	__STDIO_LOCK(stream);
	if (stream->_r > 0) {
		--stream->_r;
		r = *stream->_p++;
	} else
		r = __srget(stream);
	__STDIO_UNLOCK(stream);
	return r;
}
