#include <devices/timer.h>
#include <unistd.h>

extern void dotimer(ULONG,ULONG,struct timeval *);

int usleep(useconds_t tim)
{ struct timeval tv;

  tv.tv_secs = tim / 1000000;
  tv.tv_micro = tim % 1000000;

  dotimer(UNIT_VBLANK,TR_ADDREQUEST,&tv);
  return 0;
}
