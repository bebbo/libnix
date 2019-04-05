#include <errno.h>
#include <unistd.h>
#include "stdio.h"

long ftell(FILE *stream)
{ long pos;
  if(stream->_flags&__SERR) /* Error on stream */
  { errno=EPERM;
    return EOF; }
  if((pos=lseek(stream->file,0,SEEK_CUR))==EOF)
  { stream->_flags|=__SERR;
    return pos; }
  if(stream->_flags&__SRD)
    pos-=stream->_r+(stream->tmpp!=NULL?stream->tmpinc:0);
  else if(stream->_flags&__SWR)
    pos+=stream->_p-stream->_bf._base;
  return pos;
}
