#include "stdio.h"

int getc(FILE *fp)
{ if (--fp->incount >= 0)
    return *fp->p++;
  return __srget(fp);
}
