#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int __srget(FILE *stream) /* Get next input block */
{
  if(stream->flags&96) /* Error on stream / EOF */
  {
    stream->incount=0;
    errno=EPERM;
    return EOF;
  }
  if(stream->flags&8)
  {
    if(__fflush(stream))
      return EOF;
  }else if(stream->tmpp!=NULL) /* File is in ungetc mode */
  {
    stream->p=stream->tmpp;
    stream->incount=stream->tmpinc;
    stream->tmpp=NULL;
    if(--stream->incount>=0)
      return *stream->p++;
  }
  if(stream->flags&0x200) /* Is a sscanf buffer */
    return EOF;
  if(stream->flags&3) /* Before reading from line- or unbuffered input file */
  {                   /* fflush all line buffered output files (ANSI) */
    struct filenode *fp=(struct filenode *)__filelist.mlh_Head;
    while(fp->node.mln_Succ)
    {
      if((fp->FILE.flags&9)==9)
        __fflush(&fp->FILE); /* Don't return EOF if this fails */
      fp=(struct filenode *)fp->node.mln_Succ;
    }
  }
  stream->flags|=4;
  stream->incount=read(stream->file,stream->buffer,stream->bufsize);
  if(stream->incount==0) /* EOF found */
  {
    stream->flags|=32;
    return EOF;
  }else if(stream->incount<0) /* Error */
  {
    stream->incount=0;
    stream->flags|=64;
    return EOF;
  }
  stream->incount--;
  stream->p=stream->buffer;
  return *stream->p++;
}
