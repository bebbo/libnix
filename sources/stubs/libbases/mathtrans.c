/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* MathTransBase[2] = { (void*)-1, "mathtrans.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/mathtrans.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * MathTransBase = NULL;
__attribute__((weak)) struct MathTransIFace* IMathTrans = NULL;

void __init_MathTrans(void) __attribute__((constructor));
void __exit_MathTrans(void) __attribute__((destructor));

void __init_MathTrans(void) {
  if (MathTransBase == NULL) {
    MathTransBase = (struct Library *) IExec->OpenLibrary("mathtrans.library", 0);
    assert(MathTransBase != NULL);
  }
  if (IMathTrans == NULL) {
    IMathTrans = (struct MathTransIFace*) IExec->GetInterface((struct Library*) MathTransBase, "main", 1, NULL);
    assert(IMathTrans != NULL);
  }
}

void __exit_MathTrans(void) {
  IExec->DropInterface((struct Interface*) IMathTrans);
  IExec->CloseLibrary((struct Library*) MathTransBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
