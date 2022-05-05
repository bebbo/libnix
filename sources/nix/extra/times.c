#include <limits.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <devices/timer.h>

clock_t times(struct tms *tp)
{ struct rusage r;

  if (getrusage(RUSAGE_SELF, &r) < 0)
    return (clock_t)-1;

  tp->tms_stime = 0;
  tp->tms_utime = r.ru_utime.tv_sec * CLK_TCK +
		  (r.ru_utime.tv_usec * CLK_TCK) / 1000000;

  return tp->tms_utime;
}
