#include <stdio.h>
#include <errno.h>
#include <unistd.h>

long ftell(FILE *stream)
{
  long pos;
  if(stream->flags&64) /* Error on stream */
  { errno=EPERM;
    return EOF; }
  if((pos=lseek(stream->file,0,SEEK_CUR))==EOF)
  { stream->flags|=64;
    return pos; }
  if(stream->flags&4)
    pos-=stream->incount+(stream->tmpp!=NULL?stream->tmpinc:0);
  else if(stream->flags&8)
    pos+=stream->p-stream->buffer;
  return pos;
}
