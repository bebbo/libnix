#include <wctype.h>
#include <ctype.h>

int iswgraph(wint_t c) {
	return c < (wint_t) 0x100 ? isgraph(c) : 0;
}
