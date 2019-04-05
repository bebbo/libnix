#undef __NO_INLINE__
#define __NO_INLINE__
#include <string.h>
#include <wchar.h>

wchar_t *wmemset(wchar_t *s, wchar_t _c, size_t _n) {
	if (_n) {
		register unsigned c __asm("d0") = _c;
		register size_t n __asm("d1") = _n;
		register wchar_t * v __asm("a0") = s + n;

		size_t m = n / 8;
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
			n &= 7;
		}
		for (; n; --n)
			*--v = c;
	}
	return s;
}
