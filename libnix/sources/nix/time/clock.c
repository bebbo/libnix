#include <time.h>
#include <dos/dos.h>
#ifdef __GNUC__ /* This is very sad :-( */
#undef BITSPERBYTE
#undef MAXINT
#undef MININT
#endif
#include <limits.h>
#include <proto/dos.h>
#include <stabs.h>

static struct DateStamp ds;

int __initclock(void)
{ DateStamp(&ds);
  return 0;
}

ADD2INIT(__initclock,-10);

clock_t clock(void)
{ struct DateStamp ds2;
  DateStamp(&ds2);
  return (((ds2.ds_Days-ds.ds_Days)*(24*60)+
           ds2.ds_Minute-ds.ds_Minute)*(60*TICKS_PER_SECOND)+
          ds2.ds_Tick-ds.ds_Tick)*CLK_TCK/TICKS_PER_SECOND;
}
