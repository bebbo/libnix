#include <wchar.h>
/*
 * Yields better code.
 */
int wcsncmp(const wchar_t *p1,const wchar_t *p2, size_t n)
{
  wchar_t a,b;
  for(;;) {
	  if (n--) {
		  wchar_t c = *p1++;
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

