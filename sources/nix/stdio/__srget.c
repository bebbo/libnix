#include <stdio.h>
#include <errno.h>
#include <unistd.h>

extern int __fflush(FILE *);

int __srget(FILE *stream) /* Get next input block */
{
  if(stream->_flags&(__SERR|__SEOF)) /* Error on stream / EOF */
  {
    stream->_r=0;
    errno=EPERM;
    return EOF;
  }
  if(stream->_flags&__SWR)
  {
    if(__fflush(stream))
      return EOF;
  }else if(stream->tmpp!=NULL) /* File is in ungetc mode */
  {
    stream->_p=stream->tmpp;
    stream->_r=stream->tmpinc;
    stream->tmpp=NULL;
    if(--stream->_r>=0)
      return *stream->_p++;
  }
  if(stream->_flags&__SSTR) /* it's a sscanf buffer */
    return EOF;
  if(stream->_flags&(__SNBF|__SLBF)) /* Before reading from line- or unbuffered input file */
  {                   /* fflush all line buffered output files (ANSI) */
    struct filenode *fp=(struct filenode *)__filelist.mlh_Head;
    while(fp->node.mln_Succ)
    {
      if((fp->theFILE._flags&(__SWR|__SLBF))==(__SWR|__SLBF))
        __fflush(&fp->theFILE); /* Don't return EOF if this fails */
      fp=(struct filenode *)fp->node.mln_Succ;
    }
  }
  stream->_flags|=__SRD;
  stream->_r=read(stream->file,stream->_bf._base,stream->_bf._size);
  if(!stream->_r) /* EOF found */
  {
    stream->_flags|=__SEOF;
    return EOF;
  }else if(stream->_r<0) /* Error */
  {
    stream->_r=0;
    stream->_flags|=__SERR;
    return EOF;
  }
  stream->_r--;
  stream->_p=stream->_bf._base;
  return *stream->_p++;
}
