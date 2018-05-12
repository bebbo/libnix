#include <wctype.h>
int iswcntrl(wint_t c) {
	return c < (wint_t) 0x100 ? iscntrl(c) : 0;
}
