#include <stdio.h>
#include <stdlib.h>

int setbuffer(FILE *stream,char *buf,size_t size)
{ return setvbuf(stream,buf,buf!=NULL?_IOFBF:_IONBF,size); }
