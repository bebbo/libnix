#include <string.h>

void *memset(void *s,int c,size_t n)
{ 
    unsigned long *p = (unsigned long *)s;
    unsigned char chr = (unsigned char)c;
    unsigned long lc = (chr << 24) | (chr << 16) | (chr << 8) | chr;
    unsigned char *ch;
    size_t i;
    size_t num = n / 4;
    size_t remain = n % 4;

    /* Do LONG operations most of the time to optimize memory bandwidth */
    for (i = 0; i < num; i++) {
	*p++ = lc;
    }

    ch = (unsigned char *)p;
    for (i = 0; i < remain; i++) {
	*ch++ = chr;
    }
    return s;
}
