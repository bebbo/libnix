#include <stdlib.h>
#include <string.h>

/* This is a _fast_ block move routine! */

void bcopy(const void *s1,void *s2,size_t n)
{
    memcpy(s2, s1, n);
}
