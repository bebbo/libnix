#undef __NO_INLINE__
#define __NO_INLINE__
#include <string.h>
int strcmp(const char *p1,const char *p2)
{ 
  for(;;) {
	  char c = *p1++;
	  if (c) {
		if (c == *p2++)
		  continue;
	  } else
		++p2;

	  unsigned char a = *--p1;
	  unsigned char b = *--p2;
	  return (short)a - b;
	}
}
