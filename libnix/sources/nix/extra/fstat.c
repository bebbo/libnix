#include <sys/types.h>
#include <sys/stat.h>
#include <dos/dosextens.h>
#include <proto/dos.h>
#include <string.h>

extern void __seterrno(void);

extern int __stat(struct stat *buf,struct FileInfoBlock *fib);

extern unsigned long *__stdfiledes;

int fstat(int d,struct stat *buf)
{
#if defined (__GNUC__)
  #undef DOS_BASE_NAME
  #define DOS_BASE_NAME dosbase
  struct DosLibrary *dosbase = DOSBase;
#endif
  struct FileInfoBlock *fib;
  LONG pos,len;
  BPTR fh;

  if (/*d<stdfilesize && */((fh=__stdfiledes[d]) != 0))
    if ((fib=(struct FileInfoBlock *)AllocDosObject(DOS_FIB,NULL)) != NULL)
      ;
    else
    {
      __seterrno(); return -1;
    }
  else
    return -1;

  memset(buf,0,sizeof(struct stat));

  buf->st_mode    = S_IFCHR | 0777;
  buf->st_nlink   = 1;
  buf->st_blksize = 512;
  /*buf->st_blocks  = 0;*/

  if (((struct FileHandle *)BADDR(fh))->fh_Type != NULL)
  {
    if (!ExamineFH(fh,fib))
    {
      len = 0; pos = Seek(fh,0,OFFSET_END);
      if (pos >= 0 && (IoErr() != ERROR_ACTION_NOT_KNOWN))
        len = Seek(fh,pos,OFFSET_BEGINNING);

      fib->fib_DiskKey      = (ino_t)~((LONG)fh);
      fib->fib_DirEntryType = -1;
      fib->fib_Size         = len;
      fib->fib_Protection   = 0xff0;
      fib->fib_NumBlocks    = ((len + 511) >> 9);
      DateStamp(&fib->fib_Date);
    }

    __stat(buf,fib);

    Seek(fh,0,OFFSET_CURRENT);
    if (IoErr())
      buf->st_mode = ((buf->st_mode & ~S_IFREG) | S_IFCHR);
  }

  FreeDosObject(DOS_FIB,fib); return 0;
}
