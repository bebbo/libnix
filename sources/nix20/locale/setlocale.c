#include <limits.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <dos/dos.h>
#ifndef __KICK13__
#include <libraries/locale.h>
#include <proto/locale.h>
#endif
#include <proto/exec.h>
#include "stabs.h"

extern struct LocaleBase *LocaleBase;
//extern char __localename[];
extern struct Locale *__localevec[];

/* for LC_CTYPE */
extern const unsigned char _ctype___data[];
__near
extern const unsigned char * _ctype_;
static unsigned char *ctype;

/* for LC_NUMERIC */
extern char *__decimalpoint;

/* for LC_TIME */
extern long __timezone__data;
//extern int _daylight;

struct lconv __lconv;

int __locale_mb_cur_max(void) {
	return 0xff;
}

char *setlocale(int category, const char *name) {
	static char *string = NULL;
	size_t i, a, b;
	struct Locale *vec[5];
	char *s1, *s2, c;

	// set defaults
	__lconv.decimal_point = ".";
	__lconv.thousands_sep = "";

	if (string != NULL) /* Free string if possible */
	{
		free(string);
		string = NULL;
	}

	if (category < 0 || category > 5)
		return NULL;

	if (category == LC_ALL) {
		a = 0;
		b = 4;
	} else
		a = b = category - 1;

	if (name == NULL) /* return name of current locale */
	{
		size_t s = 0;
		for (i = a; i <= b; i++) {
#ifndef __KICK13__
			if (__localevec[i] != NULL)
				s += strlen((const char *) __localevec[i]->loc_LocaleName);
			else
#endif
				s++; /* "C" locale */
		}

		if ((string = malloc(s + b - a + 1)) == NULL)
			return NULL;

		string[0] = '\0';
		for (i = a; i <= b; i++) {
#ifndef __KICK13__
			if (__localevec[i] != NULL)
				strcat(string, (const char *) __localevec[i]->loc_LocaleName);
			else
#endif
				strcat(string, "C");
			if (i != b)
				strcat(string, "\n");
		}
		return string;
	}

	string = strdup(name); /* gets freed next time or at end */

	s1 = s2 = string;
	for (i = a; i <= b; i++) {
		while (*s2 != '\0' && *s2 != '\n')
			s2++;
		c = *s2;
		*s2 = '\0';
#ifndef __KICK13__
		if (LocaleBase == NULL || (s1[0] == 'C' && s1[1] == '\0')) /* This is the only place */
			vec[i] = NULL; /* LocaleBase gets tested for NULL */
		else if ((vec[i] = OpenLocale(s1[0]=='\0'?NULL:(STRPTR)s1)) == NULL) {
			for (; i-- > a;)
				CloseLocale(vec[i]);
			return NULL;
		}
#else
		vec[i] = NULL;
#endif
		*s2 = c;
		if (c == '\0')
			s2 = string;
		s1 = s2;
	}

	for (i = a; i <= b; i++) {
#ifndef __KICK13__
		if (__localevec[i] != NULL)
			CloseLocale(__localevec[i]);
#endif
		__localevec[i] = vec[i];
	}

#ifndef __KICK13__
	if (__localevec[LC_CTYPE - 1] != NULL) {
		struct Locale *locale = __localevec[LC_CTYPE - 1];
		ctype[0] = 0;
		for (i = 0; i < 256; i++)
			ctype[i + 1] = ((IsPrint(locale,i) && !IsGraph(locale, i)) ? 128 : 0) | (IsXDigit(locale,i) ? 64 : 0) | (IsCntrl(locale,i) ? 32 : 0) | (IsPunct(locale,i) ? 16 : 0)
					| (IsSpace(locale,i) ? 8 : 0) | (IsDigit(locale,i) ? 4 : 0) | (IsLower(locale,i) ? 2 : 0) | (IsUpper(locale,i) ? 1 : 0);
		_ctype_ = ctype;
	} else
#endif
		_ctype_ = _ctype___data;

#ifndef __KICK13__
	if (__localevec[LC_MONETARY - 1] != NULL) {
		struct Locale *locale = __localevec[LC_MONETARY - 1];
		__lconv.int_curr_symbol = (char *) locale->loc_MonIntCS;
		__lconv.currency_symbol = (char *) locale->loc_MonCS;
		__lconv.mon_decimal_point = (char *) locale->loc_MonDecimalPoint;
		__lconv.mon_thousands_sep = (char *) locale->loc_MonGroupSeparator;
		__lconv.mon_grouping = (char *) locale->loc_MonFracGrouping;
		__lconv.positive_sign = (char *) locale->loc_MonPositiveSign;
		__lconv.negative_sign = (char *) locale->loc_MonNegativeSign;
		__lconv.int_frac_digits = locale->loc_MonIntFracDigits;
		__lconv.frac_digits = locale->loc_MonFracDigits;
		__lconv.p_cs_precedes = locale->loc_MonPositiveCSPos;
		__lconv.p_sep_by_space = locale->loc_MonPositiveSpaceSep;
		__lconv.p_sign_posn = locale->loc_MonPositiveSignPos;
		__lconv.n_cs_precedes = locale->loc_MonNegativeCSPos;
		__lconv.n_sep_by_space = locale->loc_MonNegativeSpaceSep;
		__lconv.n_sign_posn = locale->loc_MonNegativeSignPos;
	} else
#endif
	{
		__lconv.int_curr_symbol = "";
		__lconv.currency_symbol = "";
		__lconv.mon_decimal_point = "";
		__lconv.mon_thousands_sep = "";
		__lconv.mon_grouping = "";
		__lconv.positive_sign = "";
		__lconv.negative_sign = "";
		__lconv.int_frac_digits = CHAR_MAX;
		__lconv.frac_digits = CHAR_MAX;
		__lconv.p_cs_precedes = CHAR_MAX;
		__lconv.p_sep_by_space = CHAR_MAX;
		__lconv.p_sign_posn = CHAR_MAX;
		__lconv.n_cs_precedes = CHAR_MAX;
		__lconv.n_sep_by_space = CHAR_MAX;
		__lconv.n_sign_posn = CHAR_MAX;
	}

	if (__localevec[LC_NUMERIC - 1] != NULL) {
		struct Locale *locale = __localevec[LC_NUMERIC - 1];
#ifndef __KICK13__
		__lconv.decimal_point = (char*) locale->loc_DecimalPoint;
#else
		__lconv.decimal_point = (char*) ".";
#endif
		__decimalpoint = __lconv.decimal_point;
#ifndef __KICK13__
		__lconv.thousands_sep = (char*) locale->loc_GroupSeparator;
#else
		__lconv.thousands_sep = (char*)",";
#endif
	}

#ifndef __KICK13__
	if (__localevec[LC_TIME - 1] != NULL)
		__timezone__data = __localevec[LC_TIME - 1]->loc_GMTOffset * 60;
	else
#endif
		__timezone__data = 0;

	return (char *) name;
}

void __initlocale(void) {
	if ((ctype = malloc(257)) != NULL) {
		if (setlocale(LC_ALL, "") != NULL) /* Set the default locale */
			return;
	}
}

void __exitlocale(void) {
#ifndef __KICK13__
	int i;
	for (i = 0; i < 5; i++)
		if (__localevec[i] != NULL)
			CloseLocale(__localevec[i]);
#endif
}

ADD2INIT(__initlocale, -10);
ADD2EXIT(__exitlocale, -10);

