#include "stdio.h"

#include "__filenode.h"

extern __stdargs int __fflush(FILE *stream);

int fflush(FILE *stream) /* fflush one or all files */
{ struct MinNode *node,*nextnode;
  int retval;

  if(stream!=NULL)
    return __fflush(stream);
  retval=0;
  node=__filelist.mlh_Head;
  while((nextnode=node->mln_Succ)!=NULL)
  { if(__fflush(&((struct filenode *)node)->theFILE))
      retval=EOF;
    node=nextnode; }
  return retval;
}
