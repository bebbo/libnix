#include <stdio.h>
#include <stdlib.h>

void *calloc(unsigned long nmemb,unsigned long size)
{
  unsigned long l;
  unsigned long *a;
  void *b;
  l=(nmemb*size+(sizeof(unsigned long)-1))&~(sizeof(unsigned long)-1);
  a=(unsigned long *)(b=malloc(l));
  if(b!=NULL)
  {
    do
      *a++=0;
    while((l-=sizeof(unsigned long))!=0);
  }
  return b;
}
