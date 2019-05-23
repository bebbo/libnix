#define __NO_INLINE__
#include "stdio.h"
__stdargs int ferror(FILE *fp) {
	return ((fp)->_flags & __SERR);
}
