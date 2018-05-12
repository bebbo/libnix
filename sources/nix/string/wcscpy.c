#include <wchar.h>

wchar_t *
wcscpy(wchar_t *__restrict s1, const wchar_t *__restrict s2) {
	wchar_t *s = s1;
	do
		; while ((*s1++ = *s2++));
	return s;
}
