#define __NO_INLINE__
#include "stdio.h"
__stdargs int fgetc(FILE *stream) {
	return getc(stream);
}

