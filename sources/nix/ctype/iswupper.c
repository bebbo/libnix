#include <wctype.h>
int iswupper(wint_t c) {
	return c < (wint_t) 0x100 ? isupper(c) : 0;
}
