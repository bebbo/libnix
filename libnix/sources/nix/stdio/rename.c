#include <stdio.h>
#include <string.h>
#include <dos/dos.h>
#include <proto/dos.h>

extern void __seterrno(void);
extern char *__amigapath(const char *path);

int rename(const char *old,const char *new)
{ int ret=-1;

#ifdef IXPATHS
  if((old=__amigapath(old))!=NULL)
  { 
    if((old=strdup(old))!=NULL)
    { 
      if((new=__amigapath(new))!=NULL)
      {
#endif
        if(Rename((char *)old,(char *)new))
          ret=0;
        else
          __seterrno();

#ifdef IXPATHS
      }
      free(old);
    }
  }
#endif

  return ret;
}
