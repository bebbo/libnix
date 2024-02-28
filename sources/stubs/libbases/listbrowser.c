/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* ListBrowserBase[2] = { (void*)-1, "gadgets/listbrowser.gadget" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>
#include <gadgets/listbrowser.h>

#include <interfaces/listbrowser.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * ListBrowserBase = NULL;
__attribute__((weak)) struct ListBrowserIFace* IListBrowser = NULL;

void __init_ListBrowser(void) __attribute__((constructor));
void __exit_ListBrowser(void) __attribute__((destructor));

void __init_ListBrowser(void) {
  if (ListBrowserBase == NULL) {
    ListBrowserBase = (struct Library *) IExec->OpenLibrary("listbrowser.library", 0);
    assert(ListBrowserBase != NULL);
  }
  if (IListBrowser == NULL) {
    IListBrowser = (struct ListBrowserIFace*) IExec->GetInterface((struct Library*) ListBrowserBase, "main", 1, NULL);
    assert(IListBrowser != NULL);
  }
}

void __exit_ListBrowser(void) {
  IExec->DropInterface((struct Interface*) IListBrowser);
  IExec->CloseLibrary((struct Library*) ListBrowserBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
