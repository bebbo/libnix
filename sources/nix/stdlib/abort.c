#include <stdlib.h>
#include <signal.h>
#include "stdio.h"

void abort(void)
{
  raise(SIGABRT);
  fputs("Program aborted\n",stderr);
  exit(127);
}
