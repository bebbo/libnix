#include <wctype.h>
#include <ctype.h>
int iswpunct(wint_t c) {
	return c < (wint_t) 0x100 ? ispunct(c) : 0;
}
