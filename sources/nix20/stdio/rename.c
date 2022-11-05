#include <string.h>
#include <dos/dos.h>
#include <proto/dos.h>
#include "stdio.h"

extern void __seterrno(void);

int rename(const char *old,const char *new)
{ int ret=-1;

#ifdef IXPATHS
extern char *__amigapath(const char *path);
  if((old=__amigapath(old))!=NULL)
  { 
    if((old=strdup(old))!=NULL)
    { 
      if((new=__amigapath(new))!=NULL)
      {
#endif
        BPTR lnew=Lock((CONST_STRPTR)new,SHARED_LOCK);
        if(lnew) {
          BPTR lold=Lock((CONST_STRPTR)old,SHARED_LOCK);
          if(lold)
            ret=SameLock(lold,lnew),UnLock(lold);
          UnLock(lnew);
        }

        if(ret) {
          if(ret==1)
            DeleteFile((CONST_STRPTR)new);
          if(ret=0,!Rename((CONST_STRPTR)old,(CONST_STRPTR)new))
            __seterrno(),ret=-1;
        }

#ifdef IXPATHS
      }
      free(old);
    }
  }
#endif

  return ret;
}
