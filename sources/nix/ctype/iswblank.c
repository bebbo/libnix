#include <wctype.h>
#include <ctype.h>
int iswblank(wint_t c) {
	return c < (wint_t) 0x100 ? isblank(c) : 0;
}
