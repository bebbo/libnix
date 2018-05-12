#include <string.h>

char *stpncpy(char *dest,const char *source, size_t n)
{
  while((*dest++=*source++) && --n > 0);
  *dest = 0;
  return(dest-1);
}
