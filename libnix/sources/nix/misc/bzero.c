#include <string.h>

void bzero(void *b,size_t len)
{ size_t n;
  if((unsigned long)b&1)
  { *((char *)b)++=0;
    len--; }
  n=len/sizeof(long);
  len-=n*sizeof(long);
  while(n--)
    *((long *)b)++=0;
  while(len--)
    *((char *)b)++=0;
}
