#include <stdlib.h>

/* This is a _fast_ block move routine */

void bcopy(const void *s1,void *s2,size_t n)
{ size_t m;
  if(!n)
    return;
  if(s2<s1)
  { if((long)s1&1)
    { *((char *)s2)++=*((char *)s1)++;
      n--; }
    if(!((long)s2&1))
    { m=n/sizeof(long);
      n&=sizeof(long)-1;
      for(;m;m--)
        *((long *)s2)++=*((long *)s1)++;
    }
    for(;n;n--)
      *((char *)s2)++=*((char *)s1)++;
  }else
  { (char *)s1+=n;
    (char *)s2+=n;
    if((long)s1&1)
    { *--((char *)s2)=*--((char *)s1);
      n--; }
    if(!((long)s2&1))
    { m=n/sizeof(long);
      n&=sizeof(long)-1;
      for(;m;m--)
        *--((long *)s2)=*--((long *)s1);
    }
    for(;n;n--)
      *--((char *)s2)=*--((char *)s1);
  }
}
