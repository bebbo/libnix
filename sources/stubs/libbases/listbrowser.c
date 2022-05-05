/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* ListBrowserBase = 0;
void ** __getListBrowserBase() { return &ListBrowserBase; }
static void * const __init[2] = { __getListBrowserBase, "listbrowser.library"};
ADD2LIB(__init);
#else
void* ListBrowserBase[2] = { 0, "listbrowser.library" };
ADD2LIB(ListBrowserBase);
#endif

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
