/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* MathIeeeSingTransBase = 0;
void ** __getMathIeeeSingTransBase() { return &MathIeeeSingTransBase; }
static void * __init[2] = { __getMathIeeeSingTransBase, "mathieeesingtrans.library"};
ADD2LIB(__init);
#else
void* MathIeeeSingTransBase[2] = { 0, "mathieeesingtrans.library" };
ADD2LIB(MathIeeeSingTransBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/mathieeesingtrans.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct MathIEEEBase * MathIeeeSingTransBase = NULL;
__attribute__((weak)) struct MathIeeeSingTransIFace* IMathIeeeSingTrans = NULL;

void __init_MathIeeeSingTrans(void) __attribute__((constructor));
void __exit_MathIeeeSingTrans(void) __attribute__((destructor));

void __init_MathIeeeSingTrans(void) {
  if (MathIeeeSingTransBase == NULL) {
    MathIeeeSingTransBase = (struct MathIEEEBase *) IExec->OpenLibrary("mathieeesingtrans.library", 0);
    assert(MathIeeeSingTransBase != NULL);
  }
  if (IMathIeeeSingTrans == NULL) {
    IMathIeeeSingTrans = (struct MathIeeeSingTransIFace*) IExec->GetInterface((struct Library*) MathIeeeSingTransBase, "main", 1, NULL);
    assert(IMathIeeeSingTrans != NULL);
  }
}

void __exit_MathIeeeSingTrans(void) {
  IExec->DropInterface((struct Interface*) IMathIeeeSingTrans);
  IExec->CloseLibrary((struct Library*) MathIeeeSingTransBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
