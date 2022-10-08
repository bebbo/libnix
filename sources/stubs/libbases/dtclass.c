/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* DTClassBase[2] = { 0, "dtclass.library" };

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
