/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* MathIeeeDoubTransBase = 0;
void ** __getMathIeeeDoubTransBase() { return &MathIeeeDoubTransBase; }
static void * __init[2] = { __getMathIeeeDoubTransBase, "mathieeedoubtrans.library"};
ADD2LIB(__init);
#else
void* MathIeeeDoubTransBase[2] = { 0, "mathieeedoubtrans.library" };
ADD2LIB(MathIeeeDoubTransBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/mathieeedoubtrans.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct MathIEEEBase * MathIeeeDoubTransBase = NULL;
__attribute__((weak)) struct MathIeeeDoubTransIFace* IMathIeeeDoubTrans = NULL;

void __init_MathIeeeDoubTrans(void) __attribute__((constructor));
void __exit_MathIeeeDoubTrans(void) __attribute__((destructor));

void __init_MathIeeeDoubTrans(void) {
  if (MathIeeeDoubTransBase == NULL) {
    MathIeeeDoubTransBase = (struct MathIEEEBase *) IExec->OpenLibrary("mathieeedoubtrans.library", 0);
    assert(MathIeeeDoubTransBase != NULL);
  }
  if (IMathIeeeDoubTrans == NULL) {
    IMathIeeeDoubTrans = (struct MathIeeeDoubTransIFace*) IExec->GetInterface((struct Library*) MathIeeeDoubTransBase, "main", 1, NULL);
    assert(IMathIeeeDoubTrans != NULL);
  }
}

void __exit_MathIeeeDoubTrans(void) {
  IExec->DropInterface((struct Interface*) IMathIeeeDoubTrans);
  IExec->CloseLibrary((struct Library*) MathIeeeDoubTransBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
