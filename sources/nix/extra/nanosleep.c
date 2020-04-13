#include <sys/_timeval.h>
#include <devices/timer.h>
#include <unistd.h>

extern void dotimer(ULONG,struct timeval *);

int nanosleep(const struct timespec *req, struct timespec *rem)
{ struct timeval tv;

  tv.tv_secs = req->tv_sec;
  tv.tv_micro = req->tv_nsec / 1000;

  dotimer(TR_ADDREQUEST,&tv);
  if (rem) {
	  rem->tv_sec = 0;
	  rem->tv_nsec = 0;
  }
  return 0;
}
