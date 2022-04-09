/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* IntuitionBase = 0;
void ** __getIntuitionBase() { return &IntuitionBase; }
static void * __init[2] = { __getIntuitionBase, "intuition.library"};
ADD2LIB(__init);
#else
void* IntuitionBase[2] = { 0, "intuition.library" };
ADD2LIB(IntuitionBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>
#include <intuition/cghooks.h>
#include <intuition/classusr.h>

#include <interfaces/intuition.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct IntuitionBase * IntuitionBase = NULL;
__attribute__((weak)) struct IntuitionIFace* IIntuition = NULL;

void __init_Intuition(void) __attribute__((constructor));
void __exit_Intuition(void) __attribute__((destructor));

void __init_Intuition(void) {
  if (IntuitionBase == NULL) {
    IntuitionBase = (struct IntuitionBase *) IExec->OpenLibrary("intuition.library", 0);
    assert(IntuitionBase != NULL);
  }
  if (IIntuition == NULL) {
    IIntuition = (struct IntuitionIFace*) IExec->GetInterface((struct Library*) IntuitionBase, "main", 1, NULL);
    assert(IIntuition != NULL);
  }
}

void __exit_Intuition(void) {
  IExec->DropInterface((struct Interface*) IIntuition);
  IExec->CloseLibrary((struct Library*) IntuitionBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
