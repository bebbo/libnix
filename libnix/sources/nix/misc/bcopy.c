#include <stdlib.h>
#include <string.h>

void bcopy(const void *s1,void *s2,size_t n)
{
    unsigned char *ch1 = s1;
    unsigned char *ch2 = s2;
    if (ch1 < ch2) {
	while (n > 0) {
	    *ch2++ = *ch1++;
	    n--;
	}
    } else {
	ch1 += n;
	ch2 += n;
	while (n > 0) {
	    *ch2-- = *ch1--;
	    n--;
	}
    }
}
