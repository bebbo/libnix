/* 10-Apr-94 bug fix M. Fleischer
 * 11-Apr-94 bug fix & readjustment G. Nikl
 * 14-Apr-94 readjustment M. Fleischer
 * 24-Apr-94 cleanup for malloc changed
 */

#include <stdlib.h>
#include <exec/lists.h>
#include <exec/memory.h>
#include <proto/exec.h>
#include "stabs.h"

extern ULONG _MSTEP;

struct MinList __memorylist= /* memorylist (empty): free needs also access */
{
  (struct MinNode *)&__memorylist.mlh_Tail,
  NULL,
  (struct MinNode *)&__memorylist.mlh_Head
};

void *malloc(size_t size)
{
  struct MinNode *node=__memorylist.mlh_Head;
  struct MemHeader *b;
  ULONG size2,*a;

  size+=sizeof(ULONG);
  while(node->mln_Succ) /* yet some memory in my list ? */
  {
    if((a=Allocate((struct MemHeader *)node,size))!=NULL)
    { 
      *a++=size;
      return a;
    }
    node=node->mln_Succ;
  }
  size2=sizeof(struct MemHeader)+sizeof(ULONG)+size; /* Total memory needed */
  if(size2<=_MSTEP)
    size2=_MSTEP; /* Allocate a _MSTEP bytes large block if possible */
  size2=(size2+4095)&~4095; /* Blow up to full MMU Page */
  if((b=(struct MemHeader *)AllocMem(size2,MEMF_ANY))!=NULL)
  {
    b->mh_Lower=b->mh_First=(struct MemChunk *)(b+1);
    b->mh_First->mc_Next=NULL;
    b->mh_Free=b->mh_First->mc_Bytes=size2-sizeof(struct MemHeader);
    b->mh_Upper=(char *)b+size2;
    AddHead((struct List *)&__memorylist,&b->mh_Node);
    a=Allocate(b,size); /* It has to work this time */
    *a++=size;
    return a;
  }
  return NULL;
}

void __exitmalloc(void)
{ struct MemHeader *a;
  while((a=(struct MemHeader *)RemHead((struct List *)&__memorylist))!=NULL)
    FreeMem(a,(char *)a->mh_Upper-(char *)a); /* free all memory */
}

ADD2EXIT(__exitmalloc,-50);
