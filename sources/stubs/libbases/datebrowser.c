/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* DateBrowserBase = 0;
void ** __getDateBrowserBase() { return &DateBrowserBase; }
static void * const __init[2] = { __getDateBrowserBase, "datebrowser.library"};
ADD2LIB(__init);
#else
void* DateBrowserBase[2] = { 0, "datebrowser.library" };
ADD2LIB(DateBrowserBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/datebrowser.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * DateBrowserBase = NULL;
__attribute__((weak)) struct DateBrowserIFace* IDateBrowser = NULL;

void __init_DateBrowser(void) __attribute__((constructor));
void __exit_DateBrowser(void) __attribute__((destructor));

void __init_DateBrowser(void) {
  if (DateBrowserBase == NULL) {
    DateBrowserBase = (struct Library *) IExec->OpenLibrary("datebrowser.library", 0);
    assert(DateBrowserBase != NULL);
  }
  if (IDateBrowser == NULL) {
    IDateBrowser = (struct DateBrowserIFace*) IExec->GetInterface((struct Library*) DateBrowserBase, "main", 1, NULL);
    assert(IDateBrowser != NULL);
  }
}

void __exit_DateBrowser(void) {
  IExec->DropInterface((struct Interface*) IDateBrowser);
  IExec->CloseLibrary((struct Library*) DateBrowserBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
