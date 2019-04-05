#include <stdlib.h>

/* This is a _fast_ block move routine! */
typedef union {
	void *v;
	char *c;
	short *s;
	long *l;
} val;
void bcopy(const void *s1, void *s2, size_t n) {
	size_t m;
	val v1, v2;
	if (!n)
		return;

	v1.v = (void *)s1;
	v2.v = s2;

	if (s2 < s1) {
		if (n > 15) {
			if ((long) s1 & 1) {
				*v2.c++ = *v1.c++;
				n--;
			}
			if (!((long) s2 & 1)) {
				if ((long) s1 & 2) {
					*v2.s++ = *v1.s++;
					n -= 2;
				}
				for (m = n / (8 * sizeof(long)); m; --m) {
					*v2.l++ = *v1.l++;
					*v2.l++ = *v1.l++;
					*v2.l++ = *v1.l++;
					*v2.l++ = *v1.l++;
					*v2.l++ = *v1.l++;
					*v2.l++ = *v1.l++;
					*v2.l++ = *v1.l++;
					*v2.l++ = *v1.l++;
				}
				n &= 8 * sizeof(long) - 1;
				for (m = n / sizeof(long); m; --m)
					*v2.l++ = *v1.l++;
				n &= sizeof(long) - 1;
			}
			if (!n)
				return;
		}
		while (*v2.c++ = *v1.c++, --n){}
	} else {
		v1.c += n;
		v2.c += n;
		if (n > 15) {
			if ((long) s1 & 1) {
				*--v2.c = *--v1.c;
				n--;
			}
			if (!((long) s2 & 1)) {
				if ((long) s1 & 2) {
					*--v2.s = *--v1.s;
					n -= 2;
				}
				for (m = n / (8 * sizeof(long)); m; --m) {
					*--v2.l = *--v1.l;
					*--v2.l = *--v1.l;
					*--v2.l = *--v1.l;
					*--v2.l = *--v1.l;
					*--v2.l = *--v1.l;
					*--v2.l = *--v1.l;
					*--v2.l = *--v1.l;
					*--v2.l = *--v1.l;
				}
				n &= 8 * sizeof(long) - 1;
				for (m = n / sizeof(long); m; --m)
					*--v2.l = *--v1.l;
				n &= sizeof(long) - 1;
			}
			if (!n)
				return;
		}
		while (*--v2.c = *--v1.c, --n){}
	}
}
