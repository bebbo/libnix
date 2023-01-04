#include <string.h>

union V {
	void *v;
	char *c;
	short *s;
	long *l;
};

void *memset(void *s, int _c, size_t n) {
	register unsigned c __asm("d2") = _c;
	if (n < 8) {
	    char * p = (char *) s;
		if (n) {
			*p++ = c;
			if (--n) {
				*p++ = c;
				if (--n) {
					*p++ = c;
					if (--n) {
						*p++ = c;
						if (--n) {
							*p++ = c;
							if (--n) {
								*p++ = c;
								if (--n) {
									*p++ = c;
									if (--n) {
										*p = c;
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
	    register char * p __asm("a0") = n + (char *) s;

		c = _c & 0xff;
		c |= c << 8;
		c |= c << 16;

		if ((long) p & 1) {
			__asm("move.b d2,-(a0)" :: "r" (c, p));
			--n;
		}
		if ((long) p & 2) {
			__asm("move.w d2,-(a0)" :: "r" (c,p));
			__asm("subq #2,d1");
		}
		size_t m  = n / (8 * sizeof(long));
		if (m) {
			__asm("move.l d2,a6" ::"r" (c): "a6");
			__asm("move.l d2,d5" ::"r" (c): "d5");
			__asm("move.l d2,d6" ::"r" (c): "d6");
			__asm("move.l d2,d7" ::"r" (c): "d7");
			__asm("move.l d2,a1" ::"r" (c): "a1");
			__asm("move.l d2,a2" ::"r" (c): "a2");
			__asm("move.l d2,a3" ::"r" (c): "a3");
			while (m--) {
				__asm("movem.l d2/d5/d6/d7/a1/a2/a3/a6,-(a0)" ::"r" (c, p));
			}
			n &= (8 * sizeof(long) - 1);
		}
        {
		    size_t k = n >> 2;
			for (; k; --k) {
				__asm("move.l d2,-(a0)" :: "r" (c, p));
			}
			n &= sizeof(long) - 1;
		}

		while(n--) {
			__asm("move.b d2,-(a0)" :: "r" (c, p));
		}

		return s;
	}
}
