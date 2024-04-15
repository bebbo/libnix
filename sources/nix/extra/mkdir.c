#include <proto/dos.h>
#include <sys/types.h>
#include <sys/stat.h>

extern void __seterrno(void);

int mkdir(const char *name, mode_t mode)
{
  BPTR fl;
  int ret;

  if ((fl=CreateDir((STRPTR)name)))
  {
    UnLock(fl); ret=chmod(name,mode);
  }
  else
  {
    __seterrno(); ret=-1;
  }
  return ret;
}
