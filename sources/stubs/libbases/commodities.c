/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* CxBase[2] = { 0, "commodities.library" };
ADD2LIB(CxBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <exec/nodes.h>
#include <libraries/commodities.h>
#include <devices/inputevent.h>
#include <devices/keymap.h>

#include <interfaces/commodities.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * CxBase = NULL;
__attribute__((weak)) struct CxIFace* ICx = NULL;

void __init_Cx(void) __attribute__((constructor));
void __exit_Cx(void) __attribute__((destructor));

void __init_Cx(void) {
  if (CxBase == NULL) {
    CxBase = (struct Library *) IExec->OpenLibrary("commodities.library", 0);
    assert(CxBase != NULL);
  }
  if (ICx == NULL) {
    ICx = (struct CxIFace*) IExec->GetInterface((struct Library*) CxBase, "main", 1, NULL);
    assert(ICx != NULL);
  }
}

void __exit_Cx(void) {
  IExec->DropInterface((struct Interface*) ICx);
  IExec->CloseLibrary((struct Library*) CxBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
