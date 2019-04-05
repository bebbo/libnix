#include <wchar.h>
#include "stdio.h"

#undef getwc

wint_t getwc(FILE *fp) {
	return fgetwc(fp);
}
