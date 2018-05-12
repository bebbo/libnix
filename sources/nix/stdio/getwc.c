#include <stdio.h>
#include <wchar.h>

#undef getwc

wint_t getwc(FILE *fp) {
	return fgetwc(fp);
}
