#include <devices/timer.h>
#include <unistd.h>

extern void dotimer(ULONG,struct timeval *);

int nanosleep(const struct timespec *req, struct timespec *rem)
{ struct timeval tv;

  tv.tv_secs = req->tv_secs;
  tv.tv_micro = req->tv_nsec / 1000;

  dotimer(TR_ADDREQUEST,&tv);
  if (rem) {
	  rem->tv_secs = 0;
	  rem->tv_nsec = 0;
  }
  return 0;
}
