#include <fcntl.h>
#include <unistd.h>
#include <dos/dos.h>
#include <proto/dos.h>

extern void __seterrno(void);
extern char *__amigapath(const char *path);

int access (const char *name,int mode)
{ BPTR lock;

#ifdef IXPATHS
  if((name=__amigapath(name))==NULL)
    return -1;
#endif

  lock=Lock((char *)name,mode&(O_WRONLY|O_RDWR)?ACCESS_WRITE:ACCESS_READ);
  if(lock!=0l)
  { UnLock(lock);
    return 0;
  }else
  { __seterrno();
    return -1; }
}
