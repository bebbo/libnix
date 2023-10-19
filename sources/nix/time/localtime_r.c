#include <time.h>

extern long timezone;

struct tm *localtime_r(const time_t *t, struct tm *result)
{ time_t ti=*t;
  ti-=timezone*60;
  return gmtime_r(&ti, result);
}
