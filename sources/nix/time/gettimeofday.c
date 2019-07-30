#include <time.h>
#include <proto/dos.h>
#include <proto/timer.h>
#include <devices/timer.h>
#include <sys/time.h>

#define TimerBase DOSBase->dl_TimeReq->tr_node.io_Device
extern long __gmtoffset;

int gettimeofday(struct timeval * __restrict tv, struct timezone * __restrict tz) {
  if (tv) {
      GetSysTime(tv);
      tv->tv_sec += 60 * __gmtoffset;
  }
  if (tz) {
      tz->tz_dsttime = 0;
      tz->tz_minuteswest = __gmtoffset;
  }
  return 0;
}
