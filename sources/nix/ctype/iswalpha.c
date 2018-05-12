#include <wctype.h>
int iswalpha(wint_t c) {
	return c < (wint_t) 0x100 ? isalpha(c) : 0;
}
