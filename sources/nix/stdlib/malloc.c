/* 10-Apr-94 bug fix M. Fleischer
 * 11-Apr-94 bug fix & readjustment G. Nikl
 * 14-Apr-94 readjustment M. Fleischer
 * 24-Apr-94 cleanup for malloc changed
 */

#include <stdlib.h>
#include <exec/lists.h>
#include <exec/memory.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include "stabs.h"
#include "stdio.h"

#if 0

__attribute__((noinline)) void foo(void * p, int sz, int no, int na, int nz) {
	printf("trashed mem at %p sz=%d alloc #%d damaged: before %d, behind %d\n", p, sz, no, na, nz);
}
__attribute__((noinline)) void faa(void * p) {
	printf("invalid free%p\n", p);
}
#if 0
#define N 256
#define X (size + size)
#else
#define N 64
#define X 0
#endif

#define ADD (4*2 + N)

static int NO;


void * malloc(size_t size) {
	size = (size + 3) & ~3; // round up

	// protect the memory
	char * const p = (char *)AllocVec(size + X + ADD + N, MEMF_PUBLIC);

	char * q = p;
	// size
	*(int*)q = size;
	q += 4;
	// no
	*(int*)q = ++NO;
	q += 4;
	// 0 1 2 3 ... 255 before
	for (int i = 0; i < N; ++i)
		*q++ = i;
	q += size;
	// 255 254 253 ... 0 behind
	for (int i = X + N; i > 0; --i)
		*q++ = i;

	return p + ADD;
}

void free(void * _p) {
	if (!_p)
		return;

	if (1 & (long)_p) {
		faa(_p);
		return;
	}

	unsigned char * q = _p;
	q -= ADD;
	char * const p = q;
	int size = *(int*)q;
	q += 4;
	int no = *(int*)q;
	q += 4;
	int bada = 0;
	for (int i = 0; i < N; ++i)
		if (*q++ != (unsigned char)i)
			++bada;
	q += size;

	int badz = 0;
	for (int i = X + N; i > 0; --i)
		if (*q++ != (unsigned char)i)
			++badz;

	if (bada + badz)
		foo(p, size, no, bada, badz);
	else
		FreeVec(p);
}

#else
extern ULONG _MSTEP;

struct MinList __memorylist; /* memorylist (empty): free needs also access */
struct SignalSemaphore  *__memsema;
void *malloc(size_t size)
{
  struct MinNode *node;
  struct MemHeader *b;
  ULONG size2,*a = NULL;

  if ((int)size < 0)
	  return 0;

  size = (size + 3) & ~3;

  ObtainSemaphore(__memsema);
  node=__memorylist.mlh_Head;
  size+=sizeof(ULONG);
  while(node->mln_Succ) /* yet some memory in my list ? */
  {
    if((a=Allocate((struct MemHeader *)node,size))!=NULL)
    { 
      *a++=size;
	  goto end;
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
	if (a != NULL) {
		*a++=size;
	}
  }

 end:
  ReleaseSemaphore(__memsema);

//	printf("malloc    %08x: %8d\n", a, size); fflush(stdout);

  return a;
}

void free(void *ptr) {
	struct MemHeader *a;

	if (!ptr) /* What does that mean ????? */
	{
		return;
	}

	ObtainSemaphore(__memsema);
//  printf("free      %08x: %8d\n", ptr, ((ULONG *)ptr)[-1]); fflush(stdout);

	a = (struct MemHeader *) __memorylist.mlh_Head;
	for (;;) {
		if (((struct MinNode *) a)->mln_Succ == NULL) /* Is not in list ????? */
		{
			return;
		}

		if (ptr >= a->mh_Lower && ptr < a->mh_Upper) /* Entry found */
			break;

		a = (struct MemHeader *) ((struct MinNode *) a)->mln_Succ;
	}


  	Deallocate(a, (ULONG * )ptr - 1, ((ULONG * )ptr)[-1]);
	if (a->mh_Free == (size_t)((char *) a->mh_Upper - (char *) a->mh_Lower)) /* All free ? */
	{
		Remove(&a->mh_Node);
		FreeMem(a, (char * )a->mh_Upper - (char * )a);
	}
	ReleaseSemaphore(__memsema);
}



#define NEWLIST(l) ((l)->mlh_Head = (struct MinNode *)&(l)->mlh_Tail, \
                    (l)->mlh_Tail = NULL, \
                    (l)->mlh_TailPred = (struct MinNode *)&(l)->mlh_Head)

void __initmalloc(void)
{
  NEWLIST(&__memorylist);
  __memsema = AllocMem(sizeof(struct SignalSemaphore), MEMF_PUBLIC | MEMF_CLEAR);
  InitSemaphore(__memsema);
}

void __exitmalloc(void)
{ struct MemHeader *a;
  while((a=(struct MemHeader *)RemHead((struct List *)&__memorylist))!=NULL)
    FreeMem(a,(char *)a->mh_Upper-(char *)a); /* free all memory */
  FreeMem(__memsema, sizeof(struct SignalSemaphore));
}

ADD2EXIT(__exitmalloc,-50);
ADD2INIT(__initmalloc,-50);

#endif
