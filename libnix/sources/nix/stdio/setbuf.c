#include <stdio.h>

int setbuf(FILE *stream,char *buf)
{ return setvbuf(stream,buf,buf!=NULL?_IOFBF:_IONBF,BUFSIZ); }
