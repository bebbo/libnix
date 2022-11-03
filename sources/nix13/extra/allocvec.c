#include <exec/execbase.h>
#include <exec/memory.h>
#include <inline/exec.h>

#undef AllocDosObject
#undef FreeDosObject

#undef AllocVec
#undef FreeVec

extern void * AllocVec(unsigned, int);
extern void FreeVec(void *);

void * AllocDosObject(unsigned type, void * ti) {
	switch (type) {
	case DOS_EXALLCONTROL:
	case DOS_FIB:
		return AllocVec(sizeof(struct FileInfoBlock), MEMF_PUBLIC | MEMF_CLEAR);
	}
	return 0;
}

void FreeDosObject(unsigned type, void * ptr) {
	switch (type) {
	case DOS_EXALLCONTROL:
	case DOS_FIB:
		FreeVec(ptr);
	}
}
