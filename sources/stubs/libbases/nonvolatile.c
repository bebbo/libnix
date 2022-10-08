/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* NVBase[2] = { 0, "nonvolatile.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <exec/lists.h>
#include <libraries/nonvolatile.h>

#include <interfaces/nonvolatile.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * NVBase = NULL;
__attribute__((weak)) struct NVIFace* INV = NULL;

void __init_NV(void) __attribute__((constructor));
void __exit_NV(void) __attribute__((destructor));

void __init_NV(void) {
  if (NVBase == NULL) {
    NVBase = (struct Library *) IExec->OpenLibrary("nonvolatile.library", 0);
    assert(NVBase != NULL);
  }
  if (INV == NULL) {
    INV = (struct NVIFace*) IExec->GetInterface((struct Library*) NVBase, "main", 1, NULL);
    assert(INV != NULL);
  }
}

void __exit_NV(void) {
  IExec->DropInterface((struct Interface*) INV);
  IExec->CloseLibrary((struct Library*) NVBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
