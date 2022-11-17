#include <stdlib.h>
#include <signal.h>
#include "stdio.h"
#include <proto/dos.h>

void abort(void)
{
  raise(SIGABRT);
  Write(Output(), (APTR)"Program aborted\n", 16);
  exit(127);
}
