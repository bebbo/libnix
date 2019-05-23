#define __NO_INLINE__
#include "stdio.h"
__stdargs void clearerr(FILE *stream) {
	stream->_flags &= ~(__SERR | __SEOF);
}
