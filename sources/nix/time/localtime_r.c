#include <time.h>

struct tm *localtime_r(const time_t *t, struct tm *result)
{ time_t ti=*t;
  ti-=_timezone;
  return gmtime_r(&ti, result);
}
