#include <wctype.h>
#include <ctype.h>
int iswalnum(wint_t c) {
	return c < (wint_t) 0x100 ? isalnum(c) : 0;
}
