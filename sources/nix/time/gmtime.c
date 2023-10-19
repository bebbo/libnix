#include <time.h>

/* Rules for leap-years:
 * 1. every 4th year is a leap year
 * 2. every 100th year is none
 * 3. every 400th is one 
 * 4. 1900 was none, 2000 is one
 */

struct tm *gmtime(const time_t *t)
{
  static struct tm utim;
  return gmtime_r(t, &utim);
}
