#define __NO_INLINE__
#include <string.h>
__stdargs char *stpcpy(char *dst, const char *src) {
	while ((*dst++ = *src++)) {
	}
	return (--dst);
}

