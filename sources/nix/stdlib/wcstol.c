#include <wchar.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "stdio.h"
#include "stabs.h"

signed long wcstol(const wchar_t *nptr, wchar_t **endptr, int base) {
	const wchar_t *p = nptr;
	wchar_t *q;
	char *_q;
	unsigned long r;
	if (!(nptr && *nptr)) {
		errno = EINVAL;
		return 0;
	}
	while (isspace((int )*p))
		p++;

	int l = wcslen(p);
	char *_p = (char*) malloc(l + 1);
	if (_p) {
		errno = ENOMEM;
		return 0;
	}

	// convert wchar_t to char
	for (int i = 0; i < l; ++i)
		_p[i] = p[i];

	r = strtoul(_p, &_q, base);
	free(_p);

	// translate end
	q = (wchar_t*)p + (_q - _p);

	if (endptr != NULL) {
		if (q == p)
			*endptr = (wchar_t*) nptr;
		else
			*endptr = q;
	}
	if (*p == '-') {
		if ((signed long) r > 0) {
			errno = ERANGE;
			return LONG_MIN;
		} else
			return r;
	} else {
		if ((signed long) r < 0) {
			errno = ERANGE;
			return LONG_MAX;
		} else
			return r;
	}
}
