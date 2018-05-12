#include <wchar.h>

wchar_t *
wcsncpy(wchar_t *__restrict s1, const wchar_t *__restrict s2, size_t n) {
	wchar_t *dscan = s1;
	while (n > 0) {
		--n;
		if ((*dscan++ = *s2++) == L'\0')
			break;
	}
	while (n-- > 0)
		*dscan++ = L'\0';

	return s1;
}
