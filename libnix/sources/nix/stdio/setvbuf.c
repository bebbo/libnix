#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int setvbuf(FILE *stream,char *buf,int mode,size_t size)
{ stream->flags&=~3;
  stream->flags|=mode==_IOLBF?1:(mode==_IONBF?2:0);
  if(size!=stream->bufsize||buf!=(char *)stream->buffer)
  { if(__fflush(stream))
      return -1;
    stream->incount=0;
    stream->tmpp=0;
    stream->flags&=~4;
    mode=(buf==NULL);
    if(mode)
      if((buf=malloc(size))==NULL)
      { errno=ENOMEM;
        return -1; }
    if(stream->flags&0x80)
      free(stream->buffer);
    if(mode)
      stream->flags|=0x80;
    else
      stream->flags&=~0x80;
    stream->buffer=buf;
    stream->bufsize=size;
  } /* Need not adjust outcount, since setvbuf affects only the NEXT full buffer */
  return 0;
}
