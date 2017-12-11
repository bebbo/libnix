#ifndef _STRSUP_H
#define _STRSUP_H

#include <sys/types.h>
#include <proto/exec.h>

#ifndef __NO_INLINE__

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define __MY_INLINE__ inline
#else
#define __MY_INLINE__ extern inline
#endif

#define memcpy(s1, s2, n) CopyMem(s2, s1, n)

__MY_INLINE__ void *memmove(void *s1,const void *s2,size_t n)
{ extern void bcopy();

  bcopy(s2,s1,n); return s1;
}

__MY_INLINE__ void *memset(void *s,int c,size_t n)
{ extern void *__memset64(void *s,int c,size_t n);
  if (n) {
      if (n > 64)
	return __memset64(s, c, n);
    unsigned char *p=(unsigned char *)s;
    do;while(*p++=c,--n);
  }
  return s;
}

__MY_INLINE__ int memcmp(const void *s1,const void *s2,size_t n)
{ const unsigned char *p1=(const unsigned char *)s1,*p2=(const unsigned char *)s2;
  unsigned long r,c;

  if ((r=n))
    do;while(r=*p1++,c=*p2++,!(r-=c) && --n);
  return r;
}

__MY_INLINE__ void *memchr(const void *s,int c,size_t n)
{
  if (n) {
    unsigned char *p=(unsigned char *)s;
    do {
      if (*p++==(unsigned char)c)
        return --p;
    } while(--n);
  }
  return (void *)n;
}

__MY_INLINE__ size_t strlen(const char *string)
{ const char *s=string;

  do;while(*s++); return ~(string-s);
}

__MY_INLINE__ size_t strlen_plus_one(const char *string)
{ const char *s=string;

  do;while(*s++); return (s-string);
}

__MY_INLINE__ char *strcpy(char *s1,const char *s2)
{ char *s=s1;
  do;while((*s1++=*s2++));
  return s;
}

__MY_INLINE__ char *strupr(char *s)
{ unsigned char *s1=(unsigned char *)s;

  while(*s1) {
    if ((*s1>('a'-1)) && (*s1<('z'+1)))
      *s1-='a'-'A';
    s1++;
  }
  return s;
}

__MY_INLINE__ char *strlwr(char *s)
{ unsigned char *s1=(unsigned char *)s;

  while(*s1) {
    if ((*s1>('A'-1)) && (*s1<('Z'+1)))
      *s1+='a'-'A';
    s1++;
  }
  return s;
}

__MY_INLINE__ char *stpcpy(char *dst,const char *src)
{
  do;while((*dst++=*src++)); return(--dst);
}

#endif /* __NO_inline__ */


#endif /* _STRSUP_H */
