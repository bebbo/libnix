#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int setvbuf(FILE *stream,char *buf,int mode,size_t size)
{ short flags=stream->_flags&~(__SNBF|__SLBF);
  if(mode==_IONBF)
    flags|=__SNBF;
  else if(mode==_IOLBF)
    flags|=__SLBF;
  if(size!=(size_t)stream->_bf._size||buf!=(char *)stream->_bf._base)
  { if(__fflush(stream))
      return -1;
    stream->_r=0;
    stream->_flags=(flags&=~__SRD);
    stream->tmpp=0;
    mode=(buf==NULL);
    if(mode&&(buf=malloc(size=size?size:1))==NULL)
    { errno=ENOMEM;
      return -1; }
    if(flags&__SMBF)
      free(stream->_bf._base);
    if(mode)
      flags|=__SMBF;
    else
      flags&=~__SMBF;
    stream->_bf._base=buf;
    stream->_bf._size=size;
  } /* Need not adjust outcount, since setvbuf affects only the NEXT full buffer */
  stream->_flags=flags; return 0;
}
