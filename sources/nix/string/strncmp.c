#include <string.h>

#if 0
int strncmp(const char *s1,const char *s2,size_t n)
{ unsigned char *p1=(unsigned char *)s1,*p2=(unsigned char *)s2;
  unsigned long r,c;

  if ((r=n))
    do;while(r=*p1++,c=*p2++,!(r-=c) && (char)c && --n);
  return r;
}
#endif

/*
 * Yields better code.
 */
int strncmp(const char *p1,const char *p2, size_t n)
{
	unsigned char a,b;
  for(;;) {
	  if (n--) {
		  char c = *p1++;
		  if (c) {
			if (c == *p2++)
			  continue;
		  } else
			++p2;
		  a = *--p1;
		  b = *--p2;
		  return (short)a - b;
	  }
	  return 0;
	}
}

