#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int __fflush(FILE *stream) /* fflush exactly one file */
{
  long size,subsize;
  unsigned char *subbuf;
  if(stream->flags&0x40) /* Error on stream */
  { errno=EPERM;
    return EOF; }
  if(stream->flags&8) /* Works only on output streams */
  {
    size=stream->p-stream->buffer; /* calculate size */
    subbuf=stream->buffer;
    while(size)
    {
      if((subsize=write(stream->file,subbuf,size))<0)
      {
	stream->flags|=64; /* error flag */
	return EOF;
      }
      size-=subsize;
      subbuf+=subsize;
    }
    stream->flags&=~8; /* unset write state */
    stream->outcount=0;
    stream->linebufsize=0;
  } /* Nothing to be done for input streams */
  return 0;
}
