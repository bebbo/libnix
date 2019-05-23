#include <limits.h>
#include <string.h>
#ifndef __KICK13__
#include <libraries/locale.h>
#include <proto/locale.h>
#include <locale.h>

extern struct Locale *__localevec[];

int strcoll(const char *s1, const char *s2) {
	if (!__localevec[LC_COLLATE - 1])
		return strcmp(s1, s2);
	else
		return StrnCmp(__localevec[LC_COLLATE-1], (STRPTR )s1, (STRPTR )s2, LONG_MAX, SC_COLLATE1);
}
#else
ALIAS(strcoll,strcmp);
#endif
