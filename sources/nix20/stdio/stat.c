#include <dos/dosextens.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __KICK13__
#include <exec/execbase.h>
#include <dos/dosextens.h>

extern struct ExecBase * SysBase;

#undef AllocDosObject
#undef FreeDosObject

extern void * AllocDosObject(long, void *);
extern void FreeDosObject(long, void *);
#endif


extern int __stat(struct stat *buf,struct FileInfoBlock *fib);
extern void __seterrno(void);
extern char *__amigapath(const char *path);

asm("_lstat: .global _lstat");
int stat(const char *name,struct stat *buf)
{ APTR oldwin,*wptr=&((struct Process *)FindTask(NULL))->pr_WindowPtr;
  struct FileInfoBlock *fib;
  BPTR lock;
  int ret=-1;

#ifdef IXPATHS
  if((name=__amigapath(name))==NULL)
    return -1;
#endif

  /* avoid possible dos-requesters ;-( */

  oldwin=*wptr; *wptr=(APTR)ret;

  if((lock=Lock((STRPTR)name,SHARED_LOCK))!=0)
  {
    if((fib=(struct FileInfoBlock *)AllocDosObject(DOS_FIB,NULL))!=NULL)
    { if(Examine(lock,fib)!=DOSFALSE)
        ret=__stat(buf,fib);
      else
        __seterrno();
      FreeDosObject(DOS_FIB,fib);
    }
    else
      __seterrno();
    UnLock(lock);
  }
  else
    __seterrno();

  *wptr=oldwin;

  return ret;
}
