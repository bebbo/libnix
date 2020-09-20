#include <exec/execbase.h>
#include <inline/exec.h>

#ifdef AllocVec
#undef AllocVec
#endif

#ifdef FreeVec
#undef FreeVec
#endif

extern struct Execbase * SysBase;

void * AllocVec(unsigned size, unsigned flags) {
	unsigned * ptr = AllocMem(size += 4, flags);
	if (ptr)
		*ptr++ = size;
	return ptr;
}

void FreeVec(unsigned * ptr) {
	unsigned sz;

	if (!ptr)
		return;
	sz = *--ptr;
	FreeMem(ptr, sz);
}
