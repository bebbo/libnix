#define __NO_INLINE__
#include "stdio.h"
__stdargs int vscanf(const char *format, va_list args) {
	return vfscanf(stdin, format, args);
}
