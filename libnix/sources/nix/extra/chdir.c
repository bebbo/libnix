#include <stdlib.h>
#include <unistd.h>
#include <proto/dos.h>
#include "stabs.h"

extern void __seterrno(void);

static BPTR oldlock;
static int havelock=0;

int chdir(const char *path)
{
  BPTR fl;
  int ret;

  if ((fl=Lock((STRPTR)path,SHARED_LOCK)))
  {
    UnLock(CurrentDir(fl)); ret=0;
  }
  else
  {
    __seterrno(); ret=-1;
  }
  return ret;
}

void __initchdir(void)
{
  BPTR fl;

  if (!(fl=Lock("",SHARED_LOCK)))
    exit(20);
  oldlock=CurrentDir(fl);
  havelock=1;
}

void __exitchdir(void)
{
  if (havelock) UnLock(CurrentDir(oldlock));
}

ADD2INIT(__initchdir,-35);
ADD2EXIT(__exitchdir,-35);
