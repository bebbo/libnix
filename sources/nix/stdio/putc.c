#include "stdio.h"

int putc(int c, FILE * fp)
{ if (--fp->outcount >= 0 ||
      (fp->outcount >= fp->linebufsize && (char)(c)!='\n'))
    return *fp->p++ = c;
  return __swbuf(c, fp);
}
