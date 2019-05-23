#include <string.h>
#ifndef __KICK13__
#include <libraries/locale.h>
#include <proto/locale.h>
#include <locale.h>

extern struct Locale *__localevec[];

size_t strxfrm(char *buffer, const char *s, size_t n) {
	if (!__localevec[LC_COLLATE - 1]) {
		strncpy(buffer, s, n);
		return strlen(s);
	} else
		return StrConvert(__localevec[LC_COLLATE-1], (STRPTR )s, (STRPTR )buffer, n, SC_COLLATE1);
}
#else
ALIAS(strxfrm,strncpy);
#endif
