#define __NO_INLINE__
#include "stdio.h"
__stdargs int vprintf(const char *format, va_list args) {
	return vfprintf(stdout, format, args);
}
