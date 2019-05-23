#define __NO_INLINE__
#include "stdio.h"
__stdargs int feof(FILE * fp) {
	return ((fp)->_flags & __SEOF);
}
