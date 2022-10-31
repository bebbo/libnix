/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* IconBase[2] = { (void*)-1, "icon.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <workbench/workbench.h>
#include <datatypes/pictureclass.h>

#include <interfaces/icon.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * IconBase = NULL;
__attribute__((weak)) struct IconIFace* IIcon = NULL;

void __init_Icon(void) __attribute__((constructor));
void __exit_Icon(void) __attribute__((destructor));

void __init_Icon(void) {
  if (IconBase == NULL) {
    IconBase = (struct Library *) IExec->OpenLibrary("icon.library", 0);
    assert(IconBase != NULL);
  }
  if (IIcon == NULL) {
    IIcon = (struct IconIFace*) IExec->GetInterface((struct Library*) IconBase, "main", 1, NULL);
    assert(IIcon != NULL);
  }
}

void __exit_Icon(void) {
  IExec->DropInterface((struct Interface*) IIcon);
  IExec->CloseLibrary((struct Library*) IconBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
