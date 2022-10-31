/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* UtilityBase[2] = { (void*)-1, "utility.library" };

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
