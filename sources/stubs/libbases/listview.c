/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* ListViewBase[2] = { (void*)-1, "gadgets/listview.gadget" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/libraries.h>
#include <intuition/intuition.h>
#include <intuition/classes.h>
#include <gadgets/listview.h>

#include <interfaces/listview.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * ListViewBase = NULL;
__attribute__((weak)) struct ListViewIFace* IListView = NULL;

void __init_ListView(void) __attribute__((constructor));
void __exit_ListView(void) __attribute__((destructor));

void __init_ListView(void) {
  if (ListViewBase == NULL) {
    ListViewBase = (struct Library *) IExec->OpenLibrary("listview.gadget", 0);
    assert(ListViewBase != NULL);
  }
  if (IListView == NULL) {
    IListView = (struct ListViewIFace*) IExec->GetInterface((struct Library*) ListViewBase, "main", 1, NULL);
    assert(IListView != NULL);
  }
}

void __exit_ListView(void) {
  IExec->DropInterface((struct Interface*) IListView);
  IExec->CloseLibrary((struct Library*) ListViewBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
