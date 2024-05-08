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

int fchdir(int fd) {
	StdFileDes *sfd = _lx_fhfromfd(fd);
	if (!sfd)
		return ERROR_DIR_NOT_FOUND;

	BPTR old = CurrentDir(sfd->lx_fh);
	if (old)
		UnLock(old);
	return old != 0;
}

void __initchdir(void)
{
  BPTR fl;

  if (!(fl=Lock((CONST_STRPTR)"",SHARED_LOCK)))
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
