/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* ScrollerBase[2] = { (void*)-1, "scroller.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/scroller.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * ScrollerBase = NULL;
__attribute__((weak)) struct ScrollerIFace* IScroller = NULL;

void __init_Scroller(void) __attribute__((constructor));
void __exit_Scroller(void) __attribute__((destructor));

void __init_Scroller(void) {
  if (ScrollerBase == NULL) {
    ScrollerBase = (struct Library *) IExec->OpenLibrary("scroller.library", 0);
    assert(ScrollerBase != NULL);
  }
  if (IScroller == NULL) {
    IScroller = (struct ScrollerIFace*) IExec->GetInterface((struct Library*) ScrollerBase, "main", 1, NULL);
    assert(IScroller != NULL);
  }
}

void __exit_Scroller(void) {
  IExec->DropInterface((struct Interface*) IScroller);
  IExec->CloseLibrary((struct Library*) ScrollerBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
