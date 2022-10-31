/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* MathIeeeDoubBasBase[2] = { (void*)-1, "mathieeedoubbas.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/mathieeedoubbas.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct MathIEEEBase * MathIeeeDoubBasBase = NULL;
__attribute__((weak)) struct MathIeeeDoubBasIFace* IMathIeeeDoubBas = NULL;

void __init_MathIeeeDoubBas(void) __attribute__((constructor));
void __exit_MathIeeeDoubBas(void) __attribute__((destructor));

void __init_MathIeeeDoubBas(void) {
  if (MathIeeeDoubBasBase == NULL) {
    MathIeeeDoubBasBase = (struct MathIEEEBase *) IExec->OpenLibrary("mathieeedoubbas.library", 0);
    assert(MathIeeeDoubBasBase != NULL);
  }
  if (IMathIeeeDoubBas == NULL) {
    IMathIeeeDoubBas = (struct MathIeeeDoubBasIFace*) IExec->GetInterface((struct Library*) MathIeeeDoubBasBase, "main", 1, NULL);
    assert(IMathIeeeDoubBas != NULL);
  }
}

void __exit_MathIeeeDoubBas(void) {
  IExec->DropInterface((struct Interface*) IMathIeeeDoubBas);
  IExec->CloseLibrary((struct Library*) MathIeeeDoubBasBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
