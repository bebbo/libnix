#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
size_t
wcrtomb (char *__restrict s,
	wchar_t wc,
	mbstate_t *__restrict ps)
{
	*s = wc;
	return 1;
}
