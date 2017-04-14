#ifndef _STRSUP_H
#define _STRSUP_H

#include <sys/types.h>
#include <proto/exec.h>

#ifndef __NO_INLINE__

#define memcpy(s1, s2, n) CopyMem(s2, s1, n)

inline void *memmove(void *s1,const void *s2,size_t n)
{ extern void bcopy();

  bcopy(s2,s1,n); return s1;
}

inline void *memset(void *s,int c,size_t n)
{ extern void *__memset64(void *s,int c,size_t n);
  if (n) {
      if (n > 64)
	return __memset64(s, c, n);
    unsigned char *p=(unsigned char *)s;
    do;while(*p++=c,--n);
  }
  return s;
}

inline int memcmp(const void *s1,const void *s2,size_t n)
{ const unsigned char *p1=(const unsigned char *)s1,*p2=(const unsigned char *)s2;
  unsigned long r,c;

  if ((r=n))
    do;while(r=*p1++,c=*p2++,!(r-=c) && --n);
  return r;
}

inline void *memchr(const void *s,int c,size_t n)
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

inline size_t strlen(const char *string)
{ const char *s=string;

  do;while(*s++); return ~(string-s);
}

inline size_t strlen_plus_one(const char *string)
{ const char *s=string;

  do;while(*s++); return (s-string);
}

inline char *strcpy(char *s1,const char *s2)
{ char *s=s1;
  do;while((*s1++=*s2++));
  return s;
}
/*
inline char *strcat(char *s1,const char *s2)
{ char *s=s1;

  do;while(*s++); --s; do;while((*s++=*s2++)); return s1;
}
*/
inline int strcmp(const char *s1,const char *s2)
{ unsigned char *p1=(unsigned char *)s1, *p2=(unsigned char *)s2;
  unsigned long r,c;

  do;while(r=*p1++,c=*p2++,!(r-=c) && (char)c); return r;
}

inline char *strupr(char *s)
{ unsigned char *s1=(unsigned char *)s;

  while(*s1) {
    if ((*s1>('a'-1)) && (*s1<('z'+1)))
      *s1-='a'-'A';
    s1++;
  }
  return s;
}

inline char *strlwr(char *s)
{ unsigned char *s1=(unsigned char *)s;

  while(*s1) {
    if ((*s1>('A'-1)) && (*s1<('Z'+1)))
      *s1+='a'-'A';
    s1++;
  }
  return s;
}

inline char *stpcpy(char *dst,const char *src)
{
  do;while((*dst++=*src++)); return(--dst);
}

#endif /* __NO_inline__ */


#endif /* _STRSUP_H */
