#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

size_t fwrite(const void *ptr,size_t size,size_t nmemb,FILE *stream)
{
  signed long subsize;
  unsigned long total;
  unsigned char *b=(unsigned char *)ptr;
  if(!(total=size*nmemb)) /* Just in case size==0 */
    return total;
  do
  {
    if(stream->_w>0)
    {
      subsize=total>stream->_w?stream->_w:total;
      memcpy(stream->_p,b,subsize);
      stream->_p+=subsize;
      stream->_w-=subsize;
      b+=subsize;
      total-=subsize;
    }else
    {
      int c;
      c=*b++;
      if(putc(c,stream)==EOF)
        break;
      total--;
    }
  }while(total);
  return (b-(unsigned char *)ptr)/size;
}
