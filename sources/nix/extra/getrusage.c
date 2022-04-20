#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <string.h>
#include "stabs.h"

extern void timer(long *);

/*
** store system time at startup. getrusage will return
** (system time - time at startup) as the user time.
*/
   
static long initclock[2];

void __inittimer()
{
  timer(initclock);
}

int getrusage(int who, struct rusage *rusage)
{
  if (rusage)
  switch(who) {
    case RUSAGE_SELF: {
   	  long * clock = &rusage->ru_utime.tv_sec;
      timer(clock);
      clock[0] -= initclock[0];
      clock[1] -= initclock[1];
      if (clock[1] < 0) {
        clock[1] += 1000000;
        clock[0] --;
      }
    }
      rusage->ru_stime.tv_sec = 0;
      rusage->ru_stime.tv_usec = 0;
      return 0;
    case RUSAGE_CHILDREN:
        rusage->ru_utime.tv_sec = 0;
        rusage->ru_utime.tv_usec = 0;
        rusage->ru_stime.tv_sec = 0;
        rusage->ru_stime.tv_usec = 0;
      return 0;
  }
  errno = EINVAL;
  return -1;
}

ADD2INIT(__inittimer,1);
