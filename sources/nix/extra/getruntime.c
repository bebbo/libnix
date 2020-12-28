/*
Returns the time used so far, in microseconds.  If possible, this is
the time used by this process, else it is the elapsed time since the
process started.
*/

#include <stdlib.h>
#include <time.h>

asm("_getruntime: .global _getruntime");
long get_run_time (void)
{
  /* Fall back on clock since it's correctly implemented. */
  return clock() * 10000;
}
