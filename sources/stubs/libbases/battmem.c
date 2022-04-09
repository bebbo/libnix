/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* BattMemBase = 0;
void ** __getBattMemBase() { return &BattMemBase; }
static void * __init[2] = { __getBattMemBase, "battmem.resource"};
ADD2LIB(__init);
#else
void* BattMemBase[2] = { 0, "battmem.resource" };
ADD2LIB(BattMemBase);
#endif

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
