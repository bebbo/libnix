#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int fseek(FILE *stream,long int offset,int whence)
{
  if(stream->flags&64) /* Error on stream */
  { errno=EPERM;
    return EOF; }
  if(stream->flags&8)
    if(__fflush(stream))
      return EOF;
  if(whence==SEEK_CUR)
    offset-=stream->incount+(stream->tmpp!=NULL?stream->tmpinc:0);
  stream->incount=0;
  stream->tmpp=NULL;
  stream->flags&=~36;
  if(lseek(stream->file,offset,whence)==EOF)
  {
    stream->flags|=64;
    return EOF;
  }
  return 0;
}
