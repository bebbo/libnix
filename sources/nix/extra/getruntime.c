/*
Returns the time used so far, in microseconds.  If possible, this is
the time used by this process, else it is the elapsed time since the
process started.
*/

#include <stdlib.h>
#include <time.h>
#include <stabs.h>

long get_run_time (void)
{
  /* Fall back on clock since it's correctly implemented. */
  return clock() * 10000;
}
ALIAS(getruntime,get_run_time);
