#include <wchar.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "stdio.h"
#include "stabs.h"

signed long wcstol(const wchar_t *nptr,wchar_t **endptr,int base)
{ const wchar_t *p=nptr;
  wchar_t *q;
  unsigned long r;
  if(!(nptr && *nptr))
  { errno=EINVAL;
    return 0;
  }
  while(isspace((int)*p))
    p++;
  r=strtoul(p,&q,base);
  if(endptr!=NULL)
  { if(q==p)
      *endptr=(wchar_t *)nptr;
    else
      *endptr=q;
  }
  if(*p=='-')
  { if((signed long)r>0)
    { errno=ERANGE;
      return LONG_MIN; }
    else
      return r;
  }else
  { if((signed long)r<0)
    { errno=ERANGE;
      return LONG_MAX; }
    else
      return r;
  }
}
