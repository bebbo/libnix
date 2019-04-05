#include <wctype.h>
#include <ctype.h>
int iswlower(wint_t c) {
	return c < (wint_t) 0x100 ? islower(c) : 0;
}
