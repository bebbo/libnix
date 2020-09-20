#ifndef __stdargs
#define __stdargs
#endif

int __stdargs
ioctl (int fd, unsigned long cmd, ...)
{
  return -1;
}
