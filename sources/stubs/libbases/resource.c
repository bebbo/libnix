/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* ResourceBase[2] = { 0, "resource.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <libraries/resource.h>
#include <intuition/classusr.h>
#include <intuition/intuition.h>
#include <libraries/locale.h>
#include <utility/tagitem.h>

#include <interfaces/resource.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * ResourceBase = NULL;
__attribute__((weak)) struct ResourceIFace* IResource = NULL;

void __init_Resource(void) __attribute__((constructor));
void __exit_Resource(void) __attribute__((destructor));

void __init_Resource(void) {
  if (ResourceBase == NULL) {
    ResourceBase = (struct Library *) IExec->OpenLibrary("resource.library", 0);
    assert(ResourceBase != NULL);
  }
  if (IResource == NULL) {
    IResource = (struct ResourceIFace*) IExec->GetInterface((struct Library*) ResourceBase, "main", 1, NULL);
    assert(IResource != NULL);
  }
}

void __exit_Resource(void) {
  IExec->DropInterface((struct Interface*) IResource);
  IExec->CloseLibrary((struct Library*) ResourceBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
