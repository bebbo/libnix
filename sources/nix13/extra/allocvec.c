#include <exec/execbase.h>
#include <inline/exec.h>

extern struct Execbase * SysBase;

void * AllocVec(unsigned size, unsigned flags) {
	unsigned * ptr = AllocMem(size += 4, flags);
	if (ptr)
		*ptr++ = size;
	return ptr;
}

void FreeVec(unsigned * ptr) {
	if (!ptr)
		return;
	unsigned sz = *--ptr;
	FreeMem(ptr, sz);
}
