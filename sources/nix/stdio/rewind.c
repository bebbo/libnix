#define __NO_INLINE__
#include "stdio.h"
__stdargs void rewind(FILE *stream) {
	fseek(stream, 0, SEEK_SET);
}
