#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

wint_t fgetwc(FILE *fp) {
	wint_t b;
	if (fread((char *) &b, 1, sizeof(wint_t), fp))
		return b;
	return -1;
}
