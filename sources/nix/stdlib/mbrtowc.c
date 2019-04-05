#include <wchar.h>
#include <stdlib.h>
#include <errno.h>

#include "stdio.h"
size_t
mbrtowc (wchar_t *__restrict pwc,
	const char *__restrict s,
	size_t n,
	mbstate_t *__restrict ps)
{
	if (!n)
		return 0;
	*pwc = 0xff & *s;
	return 1;
}
