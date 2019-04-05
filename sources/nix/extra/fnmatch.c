/**
 * Coded by Stefan "Bebbo" Franke in 2019. Replacement for all that copyrighted stuff.
 */
#include <ctype.h>
#include <fnmatch.h>
#include <string.h>
#include "stdio.h"

typedef int (*fxtype)(int);

#define FX(a) {#a, is##a}
struct __fx {
	const char * name;
	fxtype fx;
} const data[] = { FX(alnum), FX(alpha), FX(blank), FX(cntrl), FX(digit), FX(lower), FX(print), FX(punct), FX(space), FX(upper), FX(xdigit), };

/**
 * Search the matching ctype function.
 */
static fxtype lookup(const char * name, size_t len) {
//	printf("%s %d, %d, %d\n", name, len, sizeof(data), sizeof(struct __fx));
	if (len == 5) {
		for (size_t i = 0; i < sizeof(data) / sizeof(struct __fx) - 1; ++i)
			if (0 == strncmp(data[i].name, name, 5))
				return data[i].fx;
	} else if (len == 6) {
		int i = sizeof(data) / sizeof(struct __fx) - 1;
		if (0 == strncmp(data[i].name, name, 6))
			return data[i].fx;
	}
	return 0;
}


#define FLAG_PATHNAME (flags & FNM_PATHNAME)
#define	FLAG_NOESCAPE (flags & FNM_NOESCAPE)
#define FLAG_INPERIOD (flags & FNM_PERIOD)
#define FLAG_CASEFOLD (flags & FNM_CASEFOLD)

int fnmatch(const char *pattern, const char *string, int flags) {
	short period = FLAG_INPERIOD;
	unsigned char c = *string;
	unsigned char p = *pattern;
	while (c && p) {
//		if (flags & 0x8000)
//			fprintf(stderr, "%s == %s\n", pattern, string);
		if (FLAG_CASEFOLD)
			c = tolower(c);
		switch (p) {
			case '*':
				if ((FLAG_PATHNAME && c == '/') || (period && c == '.')) {
					--string;
					break;
				}
				// try with '*' and rest of string
				if (!fnmatch(pattern, string + 1, flags))
					return 0;

				// skip the '*'
				--string;
				break;
			case '?':
				// skip the '?' if match isn't allowed
				if ((FLAG_PATHNAME && c == '/') || (period && c == '.'))
					--string;
				break;
			case '[': {
				if (c == '/' && FLAG_PATHNAME)
					return FNM_NOMATCH;

				const char * start = pattern;

				p = *++pattern;

				short not = 0;
				if (p == '!') {
					not = 1;
					p = *++pattern;
				}

				// unterminated '[' -> compare as characters
				if (!p) {
					pattern = start;
					p = *pattern;
					break;
				}

				short match = 0;
				do {
					if (!p) {
						match = not;
						break;
					}
					// character classes
					if (p == '[' && pattern[1] == ':') {
						const char * name = pattern += 2;
						while (*pattern && *pattern != ':')
							++pattern;
						fxtype is = lookup(name, pattern - name);
						if (*pattern == 0) {
							match = not;
							break;
						}
						if (*++pattern != ']') {
							match = not;
							break;
						}
						if (FLAG_CASEFOLD && is == isupper)
							is = islower;
						if (is)
							match |= is(c);
					} else
					// range handling
					if (pattern[1] == '-' && pattern[2] != ']') {
						pattern += 2;
						unsigned char to = *pattern;
						if (to == '\\' && !FLAG_NOESCAPE)
							to = *++pattern;
						while (!match && p <= to) {
							if (!period || c == '.') {
								if (FLAG_CASEFOLD && tolower(p) == c)
									match = 1;
								else if (p == c) {
									match = 1;
								}
							}
							++p;
						}
					} else {
						if (!period || c != '.') {
							if (FLAG_CASEFOLD)
								p = tolower(p);
							match |= p == c;
						}
					}
					p = *++pattern;
				} while (p != ']' || pattern[1] == '-');

				// goto next char if ok
				if (match != not)
					break;

				// no match - try to apply this as character compare - fall through to character compare
				pattern = start;
				p = *pattern;
			}
				/* no break */
			case '\\':
				// recompare because of fall through - could be something else
				if (p == '\\') {
					if (!FLAG_NOESCAPE && pattern[1]) {
						p = *++pattern;
					}
				}
				/* no break */
			default:
				// to character compare
				if (FLAG_CASEFOLD) {
					if (tolower(p) != c)
						return FNM_NOMATCH;
				} else if (p != c)
					return FNM_NOMATCH;
				break;
		}

		// reset dynamic period switch
		if (FLAG_PATHNAME && c == '/')
			period = FLAG_INPERIOD;
		else
			period = 0;
		// matched
		p = *++pattern;
		c = *++string;
	}

	while (p == '*')
		p = *++pattern;

//	if (flags & 0x8000)
//		fprintf(stderr, "->%d\n", !!(p || c));
	return p | c;
}
