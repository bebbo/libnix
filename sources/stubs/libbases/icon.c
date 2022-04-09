/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* IconBase = 0;
void ** __getIconBase() { return &IconBase; }
static void * __init[2] = { __getIconBase, "icon.library"};
ADD2LIB(__init);
#else
void* IconBase[2] = { 0, "icon.library" };
ADD2LIB(IconBase);
#endif

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
