#include <stdarg.h>
#include <string.h>
#include <strsup.h>
#include "stdio.h"

int vsscanf(const char *s,const char *format,va_list args)
{ FILE buffer;
  buffer._p=(unsigned char *)s;
  buffer._r=strlen(s);
  buffer._w=0;
  buffer._flags=__SSTR|__SRD;
  buffer.tmpp=NULL;
  return vfscanf(&buffer,format,args);
}
