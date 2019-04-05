#include <wchar.h>
#include "stdio.h"

#undef putwc

wint_t putwc(wchar_t wc, FILE *fp) {
	return fputwc(wc, fp);
}
