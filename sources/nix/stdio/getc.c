#include "stdio.h"

int getc(FILE *fp)
{ if (--fp->_r >= 0)
    return *fp->_p++;
  return __srget(fp);
}
