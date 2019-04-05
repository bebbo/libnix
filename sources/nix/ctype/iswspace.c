#include <wctype.h>
#include <ctype.h>

int iswspace(wint_t c) {
	return c < (wint_t) 0x100 ? isspace(c) : 0;
}
