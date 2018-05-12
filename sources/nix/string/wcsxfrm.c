#include <wchar.h>

size_t wcsxfrm(wchar_t *__restrict a, const wchar_t *__restrict b, size_t n) {
	return wcslcpy(a, b, n);
}
