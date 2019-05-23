#define __NO_INLINE__
#include <string.h>
__stdargs void *memchr(const void *s, int c, size_t n) {
	if (n) {
		unsigned char *p = (unsigned char *) s;
		do {
			if (*p++ == (unsigned char) c)
				return --p;
		} while (--n);
	}
	return (void *) n;
}
