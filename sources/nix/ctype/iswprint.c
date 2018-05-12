#include <wctype.h>
int iswprint(wint_t c) {
	return c < (wint_t) 0x100 ? isprint(c) : 0;
}
