#define __NO_INLINE__
#include "stdio.h"
__stdargs int fputc(int c, FILE *stream) {
	return putc(c, stream);
}
