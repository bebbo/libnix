/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* BattMemBase[2] = { 0, "battmem.resource" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/battmem.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * BattMemBase = NULL;
__attribute__((weak)) struct BattMemIFace* IBattMem = NULL;

void __init_BattMem(void) __attribute__((constructor));
void __exit_BattMem(void) __attribute__((destructor));

void __init_BattMem(void) {
  if (BattMemBase == NULL) {
    BattMemBase = (struct Library *) IExec->OpenLibrary("battmem.resource", 0);
    assert(BattMemBase != NULL);
  }
  if (IBattMem == NULL) {
    IBattMem = (struct BattMemIFace*) IExec->GetInterface((struct Library*) BattMemBase, "main", 1, NULL);
    assert(IBattMem != NULL);
  }
}

void __exit_BattMem(void) {
  IExec->DropInterface((struct Interface*) IBattMem);
  IExec->CloseLibrary((struct Library*) BattMemBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
