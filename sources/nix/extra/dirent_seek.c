#include <dirent.h>
#include <stdlib.h>
#include <string.h>

static long Hash(struct dirent *e)
{
  unsigned short buf[256], i, j, k, h = 0;
  const char * p = (const char *)e->d_name;
  long l = e->d_namlen;
  
  for(i = 0; i < 256; ++i)
  {
    k = i;

    for(j = 0; j < 8; ++j)
    {
      if(k & 1)
        k = (k >> 1) ^ 0xA001;
      else
        k >>= 1;
    }
    buf[i] = k;
  }
  
  while(l--)
    h = buf[(h ^ *(p++)) & 0xFF] ^ (h >> 8);
  
  return (h<<16)|(e->d_namlen<<8)|e->d_fileno;
}

long telldir(DIR *dirp)
{
  return Hash(&dirp->dd_ent);
}

void seekdir(DIR *dirp,long loc)
{
  struct dirent *d;
  
  rewinddir(dirp);
  
  while((d = readdir(dirp)))
  {
    if(Hash(d) == loc)
      break;
  }
}
