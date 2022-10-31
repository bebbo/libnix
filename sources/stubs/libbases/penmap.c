/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* PenMapBase[2] = { (void*)-1, "penmap.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/penmap.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * PenMapBase = NULL;
__attribute__((weak)) struct PenMapIFace* IPenMap = NULL;

void __init_PenMap(void) __attribute__((constructor));
void __exit_PenMap(void) __attribute__((destructor));

void __init_PenMap(void) {
  if (PenMapBase == NULL) {
    PenMapBase = (struct Library *) IExec->OpenLibrary("penmap.library", 0);
    assert(PenMapBase != NULL);
  }
  if (IPenMap == NULL) {
    IPenMap = (struct PenMapIFace*) IExec->GetInterface((struct Library*) PenMapBase, "main", 1, NULL);
    assert(IPenMap != NULL);
  }
}

void __exit_PenMap(void) {
  IExec->DropInterface((struct Interface*) IPenMap);
  IExec->CloseLibrary((struct Library*) PenMapBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
