#include <unistd.h>

asm("_getuid: .global _getuid");
asm("_geteuid: .global _geteuid");
asm("_getgid: .global _getgid");
asm("_getegid: .global _getegid");
pid_t getppid(void)
{
  return 0; /* init ;-) */
}
