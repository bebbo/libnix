/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* DTClassBase = 0;
void ** __getDTClassBase() { return &DTClassBase; }
static void * __init[2] = { __getDTClassBase, "dtclass.library"};
ADD2LIB(__init);
#else
void* DTClassBase[2] = { 0, "dtclass.library" };
ADD2LIB(DTClassBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <intuition/classes.h>
#include <intuition/classusr.h>

#include <interfaces/dtclass.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * DTClassBase = NULL;
__attribute__((weak)) struct DTClassIFace* IDTClass = NULL;

void __init_DTClass(void) __attribute__((constructor));
void __exit_DTClass(void) __attribute__((destructor));

void __init_DTClass(void) {
  if (DTClassBase == NULL) {
    DTClassBase = (struct Library *) IExec->OpenLibrary("dtclass.library", 0);
    assert(DTClassBase != NULL);
  }
  if (IDTClass == NULL) {
    IDTClass = (struct DTClassIFace*) IExec->GetInterface((struct Library*) DTClassBase, "main", 1, NULL);
    assert(IDTClass != NULL);
  }
}

void __exit_DTClass(void) {
  IExec->DropInterface((struct Interface*) IDTClass);
  IExec->CloseLibrary((struct Library*) DTClassBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
