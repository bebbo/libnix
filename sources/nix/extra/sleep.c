#include <devices/timer.h>

extern void dotimer(ULONG,struct timeval *);

void sleep(int secs)
{ struct timeval tv;

  if ((int)(tv.tv_secs=secs)>0)
  { tv.tv_micro=0;
    dotimer(TR_ADDREQUEST,&tv);
  }
}
