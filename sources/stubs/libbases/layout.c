/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* LayoutBase[2] = { 0, "layout.library" };
ADD2LIB(LayoutBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>
#include <gadgets/layout.h>

#include <interfaces/layout.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * LayoutBase = NULL;
__attribute__((weak)) struct LayoutIFace* ILayout = NULL;

void __init_Layout(void) __attribute__((constructor));
void __exit_Layout(void) __attribute__((destructor));

void __init_Layout(void) {
  if (LayoutBase == NULL) {
    LayoutBase = (struct Library *) IExec->OpenLibrary("layout.library", 0);
    assert(LayoutBase != NULL);
  }
  if (ILayout == NULL) {
    ILayout = (struct LayoutIFace*) IExec->GetInterface((struct Library*) LayoutBase, "main", 1, NULL);
    assert(ILayout != NULL);
  }
}

void __exit_Layout(void) {
  IExec->DropInterface((struct Interface*) ILayout);
  IExec->CloseLibrary((struct Library*) LayoutBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
