#include <stdio.h>

#ifdef ferror
#undef ferror
#endif

int ferror(FILE *stream)
{ return (stream->flags&64)!=0; }
