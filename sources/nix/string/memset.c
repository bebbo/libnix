#include <string.h>
void *memset(void *s, int _c, size_t _n) {
	register union {
		void *v;
		char *c;
		short *s;
		long *l;
	} v __asm("a0");
	v.v = s;

	register unsigned c __asm("d0") = _c & 0xff;
	c |= c << 8;
	c |= c << 16;

	if (_n && (long) v.l & 1) {
		*v.c++ = c;
		_n--;
	}
	if (_n > 1 && (long) v.l & 2) {
		*v.s++ = c;
		_n -= 2;
	}


	register size_t n __asm("d1") = _n;
	v.c += n;

	if (n && (long) v.l & 1) {
		--v.c;
		*v.c = c;
		n--;
	}
	if (n > 2 && (long) v.l & 2) {
		--v.s;
		*v.s = c;
		n -= 2;
	}
	size_t m = n / (8 * sizeof(long));
	__asm("move.l d0,a6" ::: "a6");
	__asm("move.l d0,d5" ::: "d5");
	__asm("move.l d0,d6" ::: "d6");
	__asm("move.l d0,d7" ::: "d7");
	__asm("move.l d0,a1" ::: "a1");
	__asm("move.l d0,a2" ::: "a2");
	__asm("move.l d0,a3" ::: "a3");
	while (m--) {
//		*v.l++ = c;
//		*v.l++ = c;
//		*v.l++ = c;
//		*v.l++ = c;
//		*v.l++ = c;
//		*v.l++ = c;
//		*v.l++ = c;
//		*v.l++ = c;
			__asm("movem.l d0/d5/d6/d7/a1/a2/a3/a6,-(a0)");
	}
	n &= (8 * sizeof(long) - 1);
	for (m = n / sizeof(long); m; --m)
		*--v.l = c;
	if ((n &= sizeof(long) - 1))
		do
			; while (*--v.c = c, --n);

	return s;
}
