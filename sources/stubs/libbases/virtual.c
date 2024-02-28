/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* VirtualBase[2] = { (void*)-1, "gadgets/virtual.gadget" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>
#include <intuition/classusr.h>
#include <gadgets/layout.h>

#include <interfaces/virtual.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * VirtualBase = NULL;
__attribute__((weak)) struct VirtualIFace* IVirtual = NULL;

void __init_Virtual(void) __attribute__((constructor));
void __exit_Virtual(void) __attribute__((destructor));

void __init_Virtual(void) {
  if (VirtualBase == NULL) {
    VirtualBase = (struct Library *) IExec->OpenLibrary("virtual.library", 0);
    assert(VirtualBase != NULL);
  }
  if (IVirtual == NULL) {
    IVirtual = (struct VirtualIFace*) IExec->GetInterface((struct Library*) VirtualBase, "main", 1, NULL);
    assert(IVirtual != NULL);
  }
}

void __exit_Virtual(void) {
  IExec->DropInterface((struct Interface*) IVirtual);
  IExec->CloseLibrary((struct Library*) VirtualBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
