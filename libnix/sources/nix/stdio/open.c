#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#undef LONGBITS
#undef BITSPERBYTE
#undef MAXINT
#undef MININT
#include <dos/dos.h>
#define DEVICES_TIMER_H
#include <dos/dosextens.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <stabs.h>

extern void __seterrno(void);
extern char *__amigapath(const char *path);
extern struct WBStartup *_WBenchMsg;

unsigned long *__stdfiledes;
static unsigned long stdfilesize=3;
static long stderrdes=0; /* The normal Amiga shell sets no process->pr_CES stream -
                          * we use Open("*",MODE_NEWFILE) in this case
                          */

void __initstdio(void)
{ unsigned long *sfd;

  if((sfd=__stdfiledes=(unsigned long *)malloc(3*sizeof(unsigned long)))==NULL)
    exit(20);
  sfd[STDIN_FILENO ]=Input();
  sfd[STDOUT_FILENO]=Output();
  if(!(sfd[STDERR_FILENO]=((struct Process *)FindTask(NULL))->pr_CES))
    if(_WBenchMsg!=NULL||!(sfd[STDERR_FILENO]=stderrdes=Open("*",MODE_OLDFILE)))
      sfd[STDERR_FILENO]=sfd[STDOUT_FILENO];
}

/* Call our private constructor */
ADD2INIT(__initstdio,-30);

void __exitstdio(void)
{ long file,*sfd;
  int i,max;

  for(sfd=&__stdfiledes[3],max=stdfilesize,i=3;i<max;i++)
    if((file=*sfd++))
      Close(file);

  if((file=stderrdes))
    Close(file);
}

/* Call our private destructor at cleanup */
ADD2EXIT(__exitstdio,-30);

int open(const char *path,int flags,...)
{
  unsigned long *sfd;
  int file,max;

#ifdef IXPATHS
  if((path=__amigapath(path))==NULL)
    return -1;
#endif

  for(sfd=__stdfiledes,max=stdfilesize,file=3;file<max;file++)
    if(!sfd[file])
      break;

  if(file>SHRT_MAX)
  { errno=EMFILE;
    return -1; }

  if(file==max)
  { if((sfd=realloc(sfd,(file+1)*sizeof(unsigned long)))==NULL)
    { errno=ENOMEM;
      return -1; }
    __stdfiledes=sfd;
    stdfilesize++;
  }

  if((sfd[file]=Open((char *)path,flags&O_TRUNC?MODE_NEWFILE:
                     flags&(O_WRONLY|O_RDWR)?MODE_READWRITE:MODE_OLDFILE)))
    return file;
  __seterrno();
  return EOF;
}

int close(int d)
{
  int ret=0;
  if(d>2)
  {
    if(!Close(__stdfiledes[d]))
    { ret=EOF;
      __seterrno(); }
    __stdfiledes[d]=0;
  }
  return ret;
}

off_t lseek(int d,off_t offset,int whence)
{
  long r,file=__stdfiledes[d];
  __chkabort();
  r=Seek(file,offset,whence==SEEK_SET?OFFSET_BEGINNING:
         whence==SEEK_END?OFFSET_END:OFFSET_CURRENT);
  if(r!=EOF)
    r=Seek(file,0,OFFSET_CURRENT);
  if(r==EOF)
    __seterrno();
  return r;
}

ssize_t read(int d,void *buf,size_t nbytes)
{
  long r;
  __chkabort();
  r=Read(__stdfiledes[d],buf,nbytes);
  if(r==EOF)
    __seterrno();
  return r;
}

ssize_t write(int d,const void *buf,size_t nbytes)
{
  long r;
  __chkabort();
  r=Write(__stdfiledes[d],(char *)buf,nbytes);
  if(r==EOF)
    __seterrno();
  return r;
}

int isatty(int d)
{ return IsInteractive(__stdfiledes[d]); }
