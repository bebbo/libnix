#include <stdio.h>

int setlinebuf(FILE *f)
{
  return setvbuf(f, NULL, _IOLBF, 0);
}
