#define __NO_INLINE__
#include "stdio.h"
__stdargs int putchar(int c) {
	return putc(c, stdout);
}

