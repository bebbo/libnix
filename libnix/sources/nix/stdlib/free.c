#include <debuglib.h>
#include <stdlib.h>
#include <proto/exec.h>
#include <exec/types.h>
#include <exec/memory.h>
#include <exec/nodes.h>
#include <exec/lists.h>

extern struct MinList __memorylist;

void free(void *ptr)
{
  struct MemHeader *a;

  if(ptr==NULL) /* What does that mean ????? */
  {
#ifdef DEBUG_LIB
    FATALERROR("NULL pointer free'd\n");
#endif
    return;
  }

  a=(struct MemHeader *)__memorylist.mlh_Head;
  for(;;)
  {
    if(((struct MinNode *)a)->mln_Succ==NULL) /* Is not in list ????? */
    {
#ifdef DEBUG_LIB
      FATALERROR("Fake memory free'd\n");
#endif
      return;
    }

    if(ptr>=a->mh_Lower&&ptr<a->mh_Upper) /* Entry found */
      break;

    a=(struct MemHeader *)((struct MinNode *)a)->mln_Succ;
  }

#ifdef DEBUG_LIB
  memset(ptr,0xcc,((ULONG *)ptr)[-1]); /* Destroy contents */
#endif

  Deallocate(a,(ULONG *)ptr-1,((ULONG *)ptr)[-1]);
  if(a->mh_Free==(char *)a->mh_Upper-(char *)a->mh_Lower) /* All free ? */
  { Remove(&a->mh_Node);
    FreeMem(a,(char *)a->mh_Upper-(char *)a); }
}
