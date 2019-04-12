/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* PopCycleBase[2] = { 0, "popcycle.library" };
ADD2LIB(PopCycleBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/popcycle.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * PopCycleBase = NULL;
__attribute__((weak)) struct PopCycleIFace* IPopCycle = NULL;

void __init_PopCycle(void) __attribute__((constructor));
void __exit_PopCycle(void) __attribute__((destructor));

void __init_PopCycle(void) {
  if (PopCycleBase == NULL) {
    PopCycleBase = (struct Library *) IExec->OpenLibrary("popcycle.library", 0);
    assert(PopCycleBase != NULL);
  }
  if (IPopCycle == NULL) {
    IPopCycle = (struct PopCycleIFace*) IExec->GetInterface((struct Library*) PopCycleBase, "main", 1, NULL);
    assert(IPopCycle != NULL);
  }
}

void __exit_PopCycle(void) {
  IExec->DropInterface((struct Interface*) IPopCycle);
  IExec->CloseLibrary((struct Library*) PopCycleBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
