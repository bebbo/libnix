#define __NO_INLINE__
#include <string.h>
__stdargs int memcmp(const void *s1, const void *s2, size_t n) {
	const unsigned char *p1 = (const unsigned char *) s1, *p2 = (const unsigned char *) s2;
	while (n-- > 0) {
		if (*p1++ == *p2++)
			continue;

		unsigned char a = *--p1;
		unsigned char b = *--p2;
		return (short) a - b;
	}
	return 0;
}
