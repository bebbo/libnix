#define __NO_INLINE__
#include "stdio.h"
__stdargs int fgetpos(FILE *stream, fpos_t *pos) {
	*pos = ftell(stream);
	return 0;
}
