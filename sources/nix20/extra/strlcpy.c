#include <ctype.h>
#include <string.h>

size_t strlcpy(char *dst, const char *src, size_t dsize) {
    const char * p = src;
    if (dsize) {
      while (dsize--) {
        if ((*dst++ = *p++) == 0)
            break;
      } 
      dst[-1] = 0;
    }

    while (*p)
        ++p;

    return p - src;
}