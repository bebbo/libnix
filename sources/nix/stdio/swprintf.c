#include "stdio.h"
#include "wchar.h"
int swprintf(wchar_t *s,size_t size,const wchar_t *format,...)
{ int retval;
  va_list args;
  va_start(args,format);
  retval=vswprintf(s,size,format,args);
  va_end(args);
  return retval;
}
