#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

size_t fread(void *ptr,size_t size,size_t nmemb,FILE *stream)
{
  signed long subsize;
  unsigned long total;
  unsigned char *b=(unsigned char *)ptr;
  if(!(total=size*nmemb)) /* Just in case size==0 */
    return total;
  do
  {
    if(stream->_r>0)
    {
      subsize=total>stream->_r?stream->_r:total;
      memcpy(b,stream->_p,subsize);
      stream->_p+=subsize;
      stream->_r-=subsize;
      b+=subsize;
      total-=subsize;
    }else
    {
      int c;
      if((c=__srget(stream))==EOF)
        break;
      *b++=c;
      total--;
    }
  }while(total);
  return (b-(unsigned char *)ptr)/size;
}
