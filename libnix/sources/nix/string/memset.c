#include <string.h>

void *memset(void *s,int c,size_t n)
{ 
    unsigned char *ch = (unsigned char *)s;
    while (n > 0) {
	*ch++ = c;
	n--;
    }
    return s;
}
