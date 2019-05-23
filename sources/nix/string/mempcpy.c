#define __NO_INLINE__
#include "string.h"
__stdargs void *mempcpy(void *to, const void *from, size_t sz) {
	return sz + (char *)memcpy(to, from, sz);
}
