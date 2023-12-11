#include <locale.h>

struct __locale_t {
	int unknown;
};

static struct __locale_t __locale;
locale_t newlocale(int category_mask, const char *locale, locale_t base) {
	return &__locale;
}

locale_t uselocale(locale_t newloc) {
	return &__locale;
}

void freelocale(locale_t locobj) {
}

char * strerror_l(int errnum, locale_t locale) {
	return strerror(errnum);
}
