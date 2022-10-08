/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* ExpansionBase[2] = { 0, "expansion.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <libraries/configvars.h>
#include <dos/filehandler.h>

#include <interfaces/expansion.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct ExpansionBase * ExpansionBase = NULL;
__attribute__((weak)) struct ExpansionIFace* IExpansion = NULL;

void __init_Expansion(void) __attribute__((constructor));
void __exit_Expansion(void) __attribute__((destructor));

void __init_Expansion(void) {
  if (ExpansionBase == NULL) {
    ExpansionBase = (struct ExpansionBase *) IExec->OpenLibrary("expansion.library", 0);
    assert(ExpansionBase != NULL);
  }
  if (IExpansion == NULL) {
    IExpansion = (struct ExpansionIFace*) IExec->GetInterface((struct Library*) ExpansionBase, "main", 1, NULL);
    assert(IExpansion != NULL);
  }
}

void __exit_Expansion(void) {
  IExec->DropInterface((struct Interface*) IExpansion);
  IExec->CloseLibrary((struct Library*) ExpansionBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
