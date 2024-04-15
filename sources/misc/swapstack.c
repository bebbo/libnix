#include <exec/execbase.h>
#include <proto/exec.h>
#include <stdlib.h>

// force using the section based init
#define __libnix__ 1

#include "stabs.h"

extern struct ExecBase *SysBase;
extern UWORD *__SaveSP;

register UWORD *a7 __asm("sp");

#if defined(__KICK13__)
extern void * AllocVec(unsigned, int);
extern void FreeVec(void *);
#endif

#undef StackSwap
#define StackSwap __StackSwap

#pragma GCC push_options
#pragma GCC optimize ("-Os")

// keeps d0/d1/a0/a1 free for local use.
void __stkswap() {
	register struct StackSwapStruct *newStack asm("a2");
	register struct ExecBase *SysBase asm("a6");
	register UWORD *tmp, *upper asm("a1"), *sp;
	struct Task *task = SysBase->ThisTask;

	Disable();

	tmp = (UWORD*) newStack->stk_Lower;
	newStack->stk_Lower = task->tc_SPLower;
	task->tc_SPLower = tmp;

	tmp = (UWORD*) newStack->stk_Upper;
	newStack->stk_Upper = (ULONG) task->tc_SPUpper;
	task->tc_SPUpper = tmp;

	// copy stack
	sp = (UWORD*) newStack->stk_Upper;
	upper = tmp;
	while (sp != a7)
		*--upper = *--sp;

	task->tc_SPReg = a7 = upper;

	Enable();
}

// performs no push/pop of a2/a6, it's not necessary...
__attribute((noinline)) void StackSwap(volatile struct StackSwapStruct *newStack) {
	asm("move.l %0,a2"::"r" (newStack));
	asm("move.l %0,a6"::"r" (SysBase));
	__stkswap();
}
#pragma GCC pop_options

/*
 * swapstack.c
 *
 * A libnix startup module to swap to a new stack if the old one is not
 * big enough (minimum value set by the value of the __stack variable).
 *
 * Code derived from a stackswap module by Kriton Kyrimis (kyrimis@theseas.ntua.gr)
 *
 * Fixed by Bebbo.
 *
 * Usage: put this snippet into your main:
 extern void __stkinit(void);
 void * __x = __stkinit;
 unsigned long __stack = YOUR_STACK_SIZE;
 */

extern unsigned long __stack;
void __request(const char *text);

static volatile struct StackSwapStruct stack;
static char *newstack;

void __stkinit() {
	ULONG size, needed = __stack;
	struct Task *task;
	char *new;
	register UWORD *upper asm("a2"), *to asm("a0"), *sp;

	/* Determine original stack size */
	task = SysBase->ThisTask;
#if defined(__KICK13__)
	task->tc_SPUpper = __SaveSP + 6;
#else
	size = (char*) task->tc_SPUpper - (char*) task->tc_SPLower;
	if (needed <= size)
		return;
#endif

	/* Round size to next long word */
	needed = (needed + (sizeof(LONG) - 1)) & ~(sizeof(LONG) - 1);

	/* Allocate new stack */
	newstack = new = AllocVec(needed, MEMF_PUBLIC);
	if (!new) {
		__request("Couldn't allocate new stack!");
		exit(RETURN_FAIL);
	}

	/* Build new stack structure */
	stack.stk_Lower = new;
	stack.stk_Upper = (ULONG) (new + needed);

	/* Copy required parts of old stack */
	to = upper = (UWORD*) stack.stk_Upper;
	sp = __SaveSP;

	while (sp != a7)
		*--to = *--sp;

	stack.stk_Pointer = to;

	/* Switch to new stack */
	StackSwap(&stack);

	__SaveSP += upper - (UWORD*) stack.stk_Upper;
}

void __stkexit() {
	ULONG size;
	register UWORD *upper asm("a2"), *to asm("a0"), *sp;

	if (!newstack)
		return;

	/* Copy required parts of old stack */
	to = upper = (UWORD*) stack.stk_Upper;
	sp = __SaveSP;

	while (sp != a7)
		*--to = *--sp;

	stack.stk_Pointer = to;

	/* Switch back to old stack */
	StackSwap(&stack);

	__SaveSP += upper - (UWORD*) stack.stk_Upper;

	/* And clean up */
	FreeVec(newstack);
}

/* The same priority as the detach module - you cannot use them both */
ADD2INIT(__stkinit, -70);
ADD2EXIT(__stkexit, -70);
