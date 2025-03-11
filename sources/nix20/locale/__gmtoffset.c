/* Greenwich mean time offset and daylight savings time flag 
 */
#include <time.h>
#include <proto/locale.h>
#include <stabs.h>

long __timezone__data = 0;
int  __daylight__data = 0;
char *__tzname__data[2] = {"GMT", "GMT"};

long * __timezone = &__timezone__data;
int  * __daylight = &__daylight__data;
char **__tzname = __tzname__data;

void tzset() {
#ifndef __KICK13__
	if (LocaleBase) {
		struct Locale * locale = OpenLocale(0);
		if (locale) {
			__timezone__data = locale->loc_GMTOffset * 60;
			CloseLocale(locale);
		}
	}
#endif
}

ADD2INIT(tzset, -11);
