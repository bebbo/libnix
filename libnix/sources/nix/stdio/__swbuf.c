#include <stdio.h>
#include <errno.h>

int __swbuf(int c,FILE *stream) /* Get next output block */
{
  int out,lbs;
  if(stream->flags&0x240) /* sprintf buffer | error on stream */
  { stream->outcount=0;
    errno=EPERM;
    return EOF;
  }else if(stream->flags&4)
  {
    stream->incount=0; /* throw away input buffer */
    stream->tmpp=NULL;
    stream->flags&=~4;
  }
  lbs=stream->flags&_IOLBF?-stream->bufsize:0;
  out=(stream->flags&_IONBF?0:stream->bufsize-1)+lbs;
  if(!(stream->flags&8)) /* File wasn't in write mode */
  { stream->p=stream->buffer; /* set buffer */
    stream->outcount=--out;   /* and buffercount */
    stream->flags|=8; }       /* and write mode */
  *stream->p++=c; /* put this character */
  if(stream->outcount<0&&(stream->outcount<lbs||(char)c=='\n'))
  { if(__fflush(stream)) /* Buffer full */
      return EOF;
    stream->p=stream->buffer; /* Set new buffer */
  }
  stream->linebufsize=lbs;
  stream->outcount=out;
  stream->flags|=8;
  return c;
}
