/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* UtilityBase = 0;
void ** __getUtilityBase() { return &UtilityBase; }
static void * const __init[2] = { __getUtilityBase, "utility.library"};
ADD2LIB(__init);
#else
void* UtilityBase[2] = { 0, "utility.library" };
ADD2LIB(UtilityBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <exec/ports.h>
#include <utility/tagitem.h>
#include <utility/date.h>
#include <utility/hooks.h>
#include <utility/name.h>

#include <interfaces/utility.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct UtilityBase * UtilityBase = NULL;
__attribute__((weak)) struct UtilityIFace* IUtility = NULL;

void __init_Utility(void) __attribute__((constructor));
void __exit_Utility(void) __attribute__((destructor));

void __init_Utility(void) {
  if (UtilityBase == NULL) {
    UtilityBase = (struct UtilityBase *) IExec->OpenLibrary("utility.library", 0);
    assert(UtilityBase != NULL);
  }
  if (IUtility == NULL) {
    IUtility = (struct UtilityIFace*) IExec->GetInterface((struct Library*) UtilityBase, "main", 1, NULL);
    assert(IUtility != NULL);
  }
}

void __exit_Utility(void) {
  IExec->DropInterface((struct Interface*) IUtility);
  IExec->CloseLibrary((struct Library*) UtilityBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
