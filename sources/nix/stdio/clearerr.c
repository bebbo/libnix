#define __NO_INLINE__
#include "stdio.h"
__stdargs void clearerr(FILE *stream) {
	__STDIO_LOCK(stream);
	stream->_flags &= ~(__SERR | __SEOF);
	__STDIO_UNLOCK(stream);
}
