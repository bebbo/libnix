#include <sys/types.h>
#include <sys/stat.h>
#include <dos/dosextens.h>
#include <proto/dos.h>
#include <strsup.h>
#include <stdio.h>

extern void __seterrno(void);

int fstat(int d,struct stat *buf)
{ extern int __stat(struct stat *buf,struct FileInfoBlock *fib);
#if defined (__GNUC__)
  #undef DOS_BASE_NAME
  #define DOS_BASE_NAME dosbase
  register APTR dosbase __asm("a6") = DOSBase;
#endif
  StdFileDes *fp = _lx_fhfromfd(d);
  struct FileInfoBlock *fib;
  LONG pos,len,fh;

  if (fp && (fh=fp->lx_fh)) {
    if ((fib=(struct FileInfoBlock *)AllocDosObject(DOS_FIB,NULL)) == NULL) {
      __seterrno(); return -1;
    }
  } else return -1;

  memset(buf,0,sizeof(*buf));

  buf->st_mode    = S_IFCHR | 0777;
  buf->st_nlink   = 1;
  buf->st_blksize = 512;
  /*buf->st_blocks  = 0;*/

  if (((struct FileHandle *)BADDR(fh))->fh_Type) {

    if (!ExamineFH(fh,fib)) {

      len = 0; pos = Seek(fh,0,OFFSET_END);
      if (pos >= 0 && (IoErr() != ERROR_ACTION_NOT_KNOWN))
        len = Seek(fh,pos,OFFSET_BEGINNING);

      fib->fib_DiskKey      = (ino_t)~((LONG)fh);
      fib->fib_DirEntryType = -1;
      fib->fib_Size         = len;
      fib->fib_Protection   = 0xff0;
      fib->fib_NumBlocks    = (len+=511,len>>=9);
      DateStamp(&fib->fib_Date);
    }

    __stat(buf,fib);

    if (Seek(fh,0,OFFSET_CURRENT),IoErr())
      buf->st_mode = ((buf->st_mode & ~S_IFREG) | S_IFCHR);
  }

  FreeDosObject(DOS_FIB,fib); return 0;
}
