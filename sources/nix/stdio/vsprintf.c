#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

int vsprintf(char *s,const char *format,va_list args)
{ int retval;
  FILE buffer;
  buffer._p=s;
  buffer._r=0;
  buffer._w=INT_MAX;
  buffer._flags=__SSTR|__SWR;
  buffer.linebufsize=0;
  retval=vfprintf(&buffer,format,args);
  buffer._w = retval;
  fputc('\0',&buffer);
  return retval;
}
