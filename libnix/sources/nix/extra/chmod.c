#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dos/dosextens.h>
#include <proto/dos.h>

extern void __seterrno(void);
extern char *__amigapath(const char *path);

int chmod(const char *name, mode_t mode)
{
#ifdef IXPATHS
  if((name=__amigapath(name))==NULL)
    return -1;
#endif
  if(!SetProtection((STRPTR)name,((mode&S_IRUSR?0:FIBF_READ)|
                                  (mode&S_IWUSR?0:FIBF_WRITE|FIBF_DELETE)|
                                  (mode&S_IXUSR?0:FIBF_EXECUTE)|
                                  (mode&S_IRGRP?FIBF_GRP_READ:0)|
                                  (mode&S_IWGRP?FIBF_GRP_WRITE|FIBF_GRP_DELETE:0)|
                                  (mode&S_IXGRP?FIBF_GRP_EXECUTE:0)|
                                  (mode&S_IROTH?FIBF_OTR_READ:0)|
                                  (mode&S_IWOTH?FIBF_OTR_WRITE|FIBF_OTR_DELETE:0)|
                                  (mode&S_IXOTH?FIBF_OTR_EXECUTE:0))))
    if(__seterrno(),errno!=ETXTBSY)
      return -1;
  return 0;
}
