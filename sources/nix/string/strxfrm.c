#include <string.h>
#include <strsup.h>
#ifndef __KICK13__
#include <libraries/locale.h>
#include <proto/locale.h>
#include <locale.h>

extern struct Locale *__localevec[];

size_t strxfrm(char *buffer,const char *s,size_t n)
{ if (!__localevec[LC_COLLATE-1])
    { strncpy(buffer,s,n); return strlen(s); }
  else
    return StrConvert(__localevec[LC_COLLATE-1],(char *)s,buffer,n,SC_COLLATE1);
}
#else
ALIAS(strxfrm,strncpy);
#endif
