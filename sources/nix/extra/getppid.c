#include <unistd.h>
#include "stabs.h"

pid_t getppid(void)
{
  return 0; /* init ;-) */
}

ALIAS(getuid, getppid);
ALIAS(geteuid, getppid);
ALIAS(getgid, getppid);
ALIAS(getegid, getppid);
