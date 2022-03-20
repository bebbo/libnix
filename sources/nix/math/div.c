#include <stdlib.h>

asm("_ldiv: .global _ldiv");
div_t div(int numer, int denom) {
	div_t r;
	r.quot = numer / denom;
	r.rem = numer % denom;
	return r;
}
