#include <wctype.h>
int iswxdigit(wint_t c) {
	return (c >= (wint_t) '0' && c <= (wint_t) '9')
			|| (c >= (wint_t) 'a' && c <= (wint_t) 'f')
			|| (c >= (wint_t) 'A' && c <= (wint_t) 'F');
}
