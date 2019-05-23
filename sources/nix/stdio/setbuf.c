#define __NO_INLINE__
#include "stdio.h"
__stdargs int setbuf(FILE *stream, char *buf) {
	return setvbuf(stream, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
}
