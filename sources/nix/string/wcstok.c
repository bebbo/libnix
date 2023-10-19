#include <wchar.h>

__stdargs wchar_t *
wcstok (register wchar_t *__restrict s,
	register const wchar_t *__restrict delim,
	wchar_t **__restrict lasts)
{
	register const wchar_t *spanp;
	register int c, sc;
	wchar_t *tok;


	if (s == NULL && (s = *lasts) == NULL)
		return (NULL);

	/*
	 * Skip (span) leading delimiters (s += wcsspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = delim; (sc = *spanp++) != L'\0';) {
		if (c == sc)  goto cont;
	}

	if (c == L'\0') {		/* no non-delimiter characters */
		*lasts = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += wcscspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (;;) {
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == L'\0')
					s = NULL;
				else
					s[-1] = L'\0';
				*lasts = s;
				return (tok);
			}
		} while (sc != L'\0');
	}
	/* NOTREACHED */
}
