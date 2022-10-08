/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* GadToolsBase[2] = { 0, "gadtools.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <intuition/intuition.h>
#include <utility/tagitem.h>
#include <libraries/gadtools.h>

#include <interfaces/gadtools.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * GadToolsBase = NULL;
__attribute__((weak)) struct GadToolsIFace* IGadTools = NULL;

void __init_GadTools(void) __attribute__((constructor));
void __exit_GadTools(void) __attribute__((destructor));

void __init_GadTools(void) {
  if (GadToolsBase == NULL) {
    GadToolsBase = (struct Library *) IExec->OpenLibrary("gadtools.library", 0);
    assert(GadToolsBase != NULL);
  }
  if (IGadTools == NULL) {
    IGadTools = (struct GadToolsIFace*) IExec->GetInterface((struct Library*) GadToolsBase, "main", 1, NULL);
    assert(IGadTools != NULL);
  }
}

void __exit_GadTools(void) {
  IExec->DropInterface((struct Interface*) IGadTools);
  IExec->CloseLibrary((struct Library*) GadToolsBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
