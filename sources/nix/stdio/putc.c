#include "stdio.h"

int putc(int c, FILE * fp)
{ if (--fp->_w >= 0 ||
      (fp->_w >= fp->linebufsize && (char)(c)!='\n'))
    return *fp->_p++ = c;
  return __swbuf(c, fp);
}
