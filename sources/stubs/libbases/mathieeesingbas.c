/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* MathIeeeSingBasBase[2] = { 0, "mathieeesingbas.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/mathieeesingbas.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct MathIEEEBase * MathIeeeSingBasBase = NULL;
__attribute__((weak)) struct MathIeeeSingBasIFace* IMathIeeeSingBas = NULL;

void __init_MathIeeeSingBas(void) __attribute__((constructor));
void __exit_MathIeeeSingBas(void) __attribute__((destructor));

void __init_MathIeeeSingBas(void) {
  if (MathIeeeSingBasBase == NULL) {
    MathIeeeSingBasBase = (struct MathIEEEBase *) IExec->OpenLibrary("mathieeesingbas.library", 0);
    assert(MathIeeeSingBasBase != NULL);
  }
  if (IMathIeeeSingBas == NULL) {
    IMathIeeeSingBas = (struct MathIeeeSingBasIFace*) IExec->GetInterface((struct Library*) MathIeeeSingBasBase, "main", 1, NULL);
    assert(IMathIeeeSingBas != NULL);
  }
}

void __exit_MathIeeeSingBas(void) {
  IExec->DropInterface((struct Interface*) IMathIeeeSingBas);
  IExec->CloseLibrary((struct Library*) MathIeeeSingBasBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
