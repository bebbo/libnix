#ifndef _HEADERS_DIRENT_H
#define _HEADERS_DIRENT_H

#include <dos/exall.h>
#include <dos/dosextens.h>

struct dirent {
  ULONG d_fileno;
  USHORT d_reclen;
  USHORT d_namlen;
  char d_name[256];
};

typedef struct _dirdesc {
  int dd_fd;
  struct dirent dd_ent;
  BPTR d_lock;
  ULONG d_count;
  LONG d_more;
  struct ExAllControl *d_eac;
  struct ExAllData *current;
  union {
    char ead[2048];
    struct FileInfoBlock fib;
  } _dirun;
} DIR;

#define d_ead _dirun.ead
#define d_info _dirun.fib

/*
** prototypes
*/

__stdargs DIR *opendir(const char *dirname);
__stdargs struct dirent *readdir(DIR *dirp);
__stdargs void rewinddir(DIR *dirp);
__stdargs int closedir(DIR *dirp);

#endif /* _HEADERS_DIRENT_H */
