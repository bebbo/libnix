#include <time.h>

extern long _timezone;

struct tm *localtime(const time_t *t)
{ time_t ti=*t;
  ti-=_timezone*60;
  return gmtime(&ti);
}
