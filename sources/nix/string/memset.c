#include <string.h>

union V {
	void *v;
	char *c;
	short *s;
	long *l;
};

void *memset(void *s, int _c, size_t _n) {
	if (_n < 8) {
		char * p = (char *) s;
		if (_n--) {
			*p++ = _c;
			if (_n--) {
				*p++ = _c;
				if (_n--) {
					*p++ = _c;
					if (_n--) {
						*p++ = _c;
						if (_n--) {
							*p++ = _c;
							if (_n--) {
								*p++ = _c;
								if (_n--) {
									*p++ = _c;
									if (_n--) {
										*p++ = _c;
									}
								}
							}
						}
					}
				}
			}
		}
		return s;
	}

	{
		register unsigned c __asm("d0");
		register size_t n __asm("d1");
		register union V v __asm("a0");
		size_t m;

		v.v = s;

		c = _c & 0xff;
		c |= c << 8;
		c |= c << 16;

		n = _n;
		v.c += n;

		if ((long) v.l & 1) {
			--v.c;
			*v.c = c;
			n--;
		}
		if ((long) v.l & 2) {
			--v.s;
			*v.s = c;
			n -= 2;
		}
		m = n / (8 * sizeof(long));
		if (m) {
			__asm("move.l d0,a6" ::: "a6");
			__asm("move.l d0,d5" ::: "d5");
			__asm("move.l d0,d6" ::: "d6");
			__asm("move.l d0,d7" ::: "d7");
			__asm("move.l d0,a1" ::: "a1");
			__asm("move.l d0,a2" ::: "a2");
			__asm("move.l d0,a3" ::: "a3");
			while (m--) {
				__asm("movem.l d0/d5/d6/d7/a1/a2/a3/a6,-(a0)");
			}
			n &= (8 * sizeof(long) - 1);
		}
		m = n / sizeof(long);
		if (m) {
			for (; m; --m) {
				*--v.l = c;
			}
			n &= sizeof(long) - 1;
		}
		while(n--) {
			*--v.c = c;
		}
		return s;
	}
}
