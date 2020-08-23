#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "stdio.h"
#include "stabs.h"

signed long long strtoll(const char *nptr,char **endptr,int base)
{ const char *p=nptr;
  char *q;
  unsigned long long r;
  if(!(nptr && *nptr))
  { errno=EINVAL;
    return 0;
  }
  while(isspace((int)*p))
    p++;
  r=strtoull(p,&q,base);
  if(endptr!=NULL)
  { if(q==p)
      *endptr=(char *)nptr;
    else
      *endptr=q;
  }
  if(*p=='-')
  { if((signed long long)r>0)
    { errno=ERANGE;
      return LLONG_MIN; }
    else
      return r;
  }else
  { if((signed long)r<0)
    { errno=ERANGE;
      return LLONG_MAX; }
    else
      return r;
  }
}

ALIAS(strtoimax, strtoll);
