#include <string.h>

#define NNN 18

void *memset(void *s, int _c, size_t n) {
	register unsigned c asm ("d2") = _c;
	register char * p asm ("a0") = n + (char *) s;

	if (n > NNN) {
		c &= 0xff;
		c |= c << 8;
		c |= c << 16;

		if ((long) p & 1) {
			asm volatile("move.b %1,-(%0)" : "+r" (p): "r" (c));
			--n;
		}
		if ((long) p & 2) {
			asm volatile("move.w %1,-(%0)" : "+r" (p) : "r" (c));
			n -= 2;
		}
		size_t m  = n / (8 * sizeof(long));
		if (m) {
			asm volatile("move.l %0,a6" ::"r" (c): "a6");
			asm volatile("move.l %0,d5" ::"r" (c): "d5");
			asm volatile("move.l %0,d6" ::"r" (c): "d6");
			asm volatile("move.l %0,d7" ::"r" (c): "d7");
			asm volatile("move.l %0,a1" ::"r" (c): "a1");
			asm volatile("move.l %0,a2" ::"r" (c): "a2");
			asm volatile("move.l %0,a3" ::"r" (c): "a3");
			while (m--) {
				asm volatile("movem.l %1/d5/d6/d7/a1/a2/a3/a6,-(%0)" : "+r" (p) :"r" (c));
			}
			n &= (8 * sizeof(long) - 1);
		}
		{
			size_t k = n >> 2;
			for (; k; --k) {
				asm volatile("move.l %1,-(%0)" : "+r" (p) : "r" (c));
			}
			n &= sizeof(long) - 1;
		}
	}

	while(n--) {
		asm volatile("move.b d2,-(%0)" : "+r" (p): "r" (c));
	}

	return p;
}
