#include <stdio.h>

#ifdef feof
#undef feof
#endif

int feof(FILE *stream)
{ return (stream->flags&32)!=0; }
