#include <stdio.h>
#include <errno.h>

int ungetc(int c,FILE *stream)
{
  if(c==EOF)
    return EOF;
  if(stream->_flags&__SERR)/* Error on stream */
  { errno=EPERM;
    return EOF; }
  if(stream->_flags&__SWR) /* File is in write mode */
    if(__fflush(stream))  /* write buffer */
      return EOF;
  if(stream->tmpp==NULL)
  { if(stream->_flags&__SRD) /* File is in read mode */
    { stream->tmpp=stream->_p; /* store actual position */
      stream->tmpinc=stream->_r;
      stream->_p=&stream->unget[4]; /* and use other buffer */
      stream->_r=0;
    }else /* File is in indeterminated state */
    { stream->tmpp=(unsigned char *)2; /* Dummy */
      stream->tmpinc=0;
      stream->_p=&stream->unget[4]; /* use other buffer */
      stream->_r=0;
      stream->_flags|=__SRD;
    }
  }
  if(stream->_r==4) /* ungetc buffer overflow */
    return EOF;
  stream->_r++;
  return *--stream->_p=c;
}
