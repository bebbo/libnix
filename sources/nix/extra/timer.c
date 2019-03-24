#include <devices/timer.h>

extern void dotimer(ULONG,struct timeval *);

void timer(long clock[2])
{
  dotimer(TR_GETSYSTIME,(struct timeval *)&clock[0]);
}
