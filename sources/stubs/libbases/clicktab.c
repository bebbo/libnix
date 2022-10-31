/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* ClickTabBase[2] = { (void*)-1, "clicktab.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/clicktab.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * ClickTabBase = NULL;
__attribute__((weak)) struct ClickTabIFace* IClickTab = NULL;

void __init_ClickTab(void) __attribute__((constructor));
void __exit_ClickTab(void) __attribute__((destructor));

void __init_ClickTab(void) {
  if (ClickTabBase == NULL) {
    ClickTabBase = (struct Library *) IExec->OpenLibrary("clicktab.library", 0);
    assert(ClickTabBase != NULL);
  }
  if (IClickTab == NULL) {
    IClickTab = (struct ClickTabIFace*) IExec->GetInterface((struct Library*) ClickTabBase, "main", 1, NULL);
    assert(IClickTab != NULL);
  }
}

void __exit_ClickTab(void) {
  IExec->DropInterface((struct Interface*) IClickTab);
  IExec->CloseLibrary((struct Library*) ClickTabBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
