#include <wchar.h>
size_t
wcslcpy (wchar_t * s1,
	const wchar_t * s2,
	size_t n)
{
	wcsncpy(s1, s2, n);
	return wcslen(s1);
}
