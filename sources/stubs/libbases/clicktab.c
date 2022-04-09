/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* ClickTabBase = 0;
void ** __getClickTabBase() { return &ClickTabBase; }
static void * __init[2] = { __getClickTabBase, "clicktab.library"};
ADD2LIB(__init);
#else
void* ClickTabBase[2] = { 0, "clicktab.library" };
ADD2LIB(ClickTabBase);
#endif

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
