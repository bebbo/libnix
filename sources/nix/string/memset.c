#include <string.h>

typedef union {
    void *v;
    char *c;
    short *s;
    long *l;
} val;
void *memset(void *s,int c,size_t n)
{ 
    size_t m;
    val v;
    v.v = s;

    if(n) { 
	if(n > 15) {
	    c *= 0x01010101;
	    if((long)v.l & 1) {
		*v.c++ = c;
		n--; 
	    }
	    if((long)v.l & 2) {
		*v.s++ = c;
		n-=2; 
	    }
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
	    if((n &= sizeof(long) - 1)==0) 
		goto leave;
	}
	do;
	while(*v.c++ = c, --n);
    }
leave:
    return s;
}
