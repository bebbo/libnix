#undef __NO_INLINE__
#include <string.h>
extern void *memset(void *s,int c,size_t n);
void *__memset64(void *s,int c,size_t n)
{
    union {
        void *v;
        char *c;
        short *s;
        long *l;
    } v;
    v.v = s;

    c = 0x01010101 * (unsigned char)c;
    if((long)v.l & 1) {
	*v.c++ = c;
	n--;
    }
    if((long)v.l & 2) {
	*v.s++ = c;
	n-=2;
    }
    size_t m;
    for(m= n / (8 * sizeof(long)); m; --m) {
	*v.l++ = c;
	*v.l++ = c;
	*v.l++ = c;
	*v.l++ = c;
	*v.l++ = c;
	*v.l++ = c;
	*v.l++ = c;
	*v.l++ = c;
    }
    n &= (8 * sizeof(long)-1);
    for(m = n / sizeof(long); m; --m)
	*v.l++ = c;
    if((n &= sizeof(long) - 1))
	do;
	while(*v.c++ = c, --n);

    return s;
}
