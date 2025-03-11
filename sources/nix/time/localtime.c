#include <time.h>

struct tm *localtime(const time_t *t)
{ time_t ti=*t;
  ti-=_timezone;
  return gmtime(&ti);
}
