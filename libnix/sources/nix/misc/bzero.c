#include <memory.h>

void bzero(void *b,size_t n)
{
    unsigned char *ch = (unsigned char *)b;
    while (n > 0) {
	*ch++ = 0;
	n--;
    }
}
