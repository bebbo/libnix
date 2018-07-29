#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int fseek(FILE *stream,long int offset,int whence)
{
  if(stream->_flags&__SERR) /* Error on stream */
  { errno=EPERM;
    return EOF; }
  if(stream->_flags&__SWR)
    if(__fflush(stream))
      return EOF;
  if(whence==SEEK_CUR)
    offset-=stream->_r+(stream->tmpp!=NULL?stream->tmpinc:0);
  stream->_r=0;
  stream->tmpp=NULL;
  stream->_flags&=~(__SEOF|__SRD);
  if(lseek(stream->file,offset,whence)==EOF)
  { stream->_flags|=__SERR;
    return EOF; }
  return 0;
}
