#include <sys/time.h>
#include <dos/dos.h>
#include <proto/dos.h>

extern long __gmtoffset;

int gettimeofday(struct timeval *tv, struct timezone *tzp)
{
  if (tv) {
    struct DateStamp t;
    DateStamp(&t); /* Get timestamp */
    tv->tv_sec=((t.ds_Days+2922)*1440+t.ds_Minute+__gmtoffset)*60+
               t.ds_Tick/TICKS_PER_SECOND;
    tv->tv_usec=(t.ds_Tick%TICKS_PER_SECOND)*1000000/TICKS_PER_SECOND;
  }
  if (tzp) {
    /* since AmigaOS doesn't support timezones, we always return
     * GMT...
     */
    tzp->tz_minuteswest = 0;
    tzp->tz_dsttime = 0;
  }

  return 0;
}

/*
 * 2922 is the number of days between 1.1.1970 and 1.1.1978 (2 leap years and 6 normal)
 * 1440 is the number of minutes per day
 *   60 is the number of seconds per minute 
 */ 
