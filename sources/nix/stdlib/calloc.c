#include <stdlib.h>

void *calloc(size_t nmemb,size_t size)
{
  size_t l=(nmemb*size+(sizeof(size_t)-1))&~(sizeof(size_t)-1);
  void *b=malloc(l);
  if(b!=NULL)
	  memset(b, 0, l);
  return b;
}
