#include <stdio.h>

void clearerr(FILE *stream)
{ stream->flags&=~96; }
