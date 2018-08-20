#include <proto/exec.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

FILE *fdopen(int filedes,const char *mode)
{ extern int _lx_addflags(int,int);
  if (mode!=NULL)
  { struct filenode *node = (struct filenode *)calloc(1,sizeof(*node));
    if(node!=NULL)
    { if((node->theFILE._bf._base=(char *)malloc(BUFSIZ))!=NULL)
      { node->theFILE._bf._size=BUFSIZ;
        node->theFILE.file=filedes;
        node->theFILE._flags|=__SMBF; /* Buffer is malloc'ed */
        if(isatty(filedes))
          node->theFILE._flags|=__SLBF; /* set linebuffered flag */
        if(_lx_addflags(filedes,*mode=='a'?O_APPEND:0)&O_WRONLY)
          node->theFILE._flags|=__SWO; /* set write-only flag */
        AddHead((struct List *)&__filelist,(struct Node *)&node->node);
        return &node->theFILE;
      }
      else
        errno=ENOMEM;
      free(node);
    }
    else
      errno=ENOMEM;
  }
  return NULL;
}
