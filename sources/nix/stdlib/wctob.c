#include <wchar.h>

int wctob(wint_t wc) {
	return wc > 0xff ? 0xff : wc;
}
