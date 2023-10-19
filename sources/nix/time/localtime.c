#include <time.h>

extern long timezone;

struct tm *localtime(const time_t *t)
{ time_t ti=*t;
  ti-=timezone*60;
  return gmtime(&ti);
}
