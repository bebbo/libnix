#include <stdio.h>
#include <exec/nodes.h>
#include <exec/lists.h>

int fflush(FILE *stream) /* fflush one or all files */
{
  int retval;
  struct MinNode *node,*nextnode;
  if(stream!=NULL)
    return __fflush(stream);
  retval=0;
  node=__filelist.mlh_Head;
  while((nextnode=node->mln_Succ)!=NULL)
  { if(__fflush(&((struct filenode *)node)->FILE))
      retval=EOF;
    node=nextnode; }
  return retval;
}
