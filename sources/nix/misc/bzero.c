#include <string.h>
typedef union {
	void *v;
	char *c;
	short *s;
	long *l;
} val;

void bzero(void *b, size_t n) {
	val v;
	size_t m;
	v.v = b;

	if (!n)
		return;
	if (n > 15) {
		if ((long) v.l & 1) {
			*v.c++ = 0;
			n--;
		}
		if ((long) v.l & 2) {
			*v.s++ = 0;
			n -= 2;
		}
		for (m = n / (8 * sizeof(long)); m; --m) {
			*v.l++ = 0;
			*v.l++ = 0;
			*v.l++ = 0;
			*v.l++ = 0;
			*v.l++ = 0;
			*v.l++ = 0;
			*v.l++ = 0;
			*v.l++ = 0;
		}
		n &= 8 * sizeof(long) - 1;
		for (m = n / sizeof(long); m; --m)
			*v.l++ = 0;
		if ((n &= sizeof(long) - 1) == 0)
			return;
	}
	while (*v.c++ = 0, --n) {
	}
}
