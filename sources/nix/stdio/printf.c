#include "stdio.h"
int printf(const char *format,...)
{ int retval;
  va_list args;
  va_start(args,format);
  retval=vfprintf(stdout, format,args);
  va_end(args);
  return retval;
}
