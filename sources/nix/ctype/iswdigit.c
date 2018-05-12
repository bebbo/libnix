#include <wctype.h>

int iswdigit(wint_t c) {
	return c >= (wint_t) '0' && c <= (wint_t) '9';
}
