#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

wint_t fputwc(wchar_t wc, FILE *fp) {
	return fwrite(&wc, 1, sizeof(wchar_t), fp);
}
