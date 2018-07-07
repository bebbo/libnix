#include <dos/dosextens.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

__stdargs int ftruncate(int d, off_t pos)
{ StdFileDes *sfd = _lx_fhfromfd(d);

  if (sfd) {
    long r;
    __chkabort();
    if((r=SetFileSize(sfd->lx_fh,pos,OFFSET_BEGINNING))!=EOF)
      return r;
    __seterrno();
  }

  return EOF;
}
