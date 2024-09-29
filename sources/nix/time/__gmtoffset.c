/* Greenwich mean time offset and daylight savings time flag 
 */
#include <time.h>

long __timezone__data = 0;
int  __daylight__data = 0;
char *__tzname__data[2];

long * __timezone = &__timezone__data;
int  * __daylight = &__daylight__data;
char **__tzname = __tzname__data;


void tzset() {

}
