#include <stdlib.h>
#include <proto/exec.h>

#include "stdio.h"

void *realloc(void *ptr,size_t size)
{
//	printf("realloc   %08x: %8d\n", ptr, size); fflush(stdout);
  void *a;
  size_t l;
  if(size)
    a=malloc(size);
  else
    a=NULL;
  if(ptr!=NULL)
  { if(a!=NULL)
    { l=((ULONG *)ptr)[-1]-sizeof(ULONG);
      l=l<size?l:size;
      CopyMem(ptr,a,l);
    }
    if(size==0||a!=NULL)
      free(ptr);
  }
  return a;
}
