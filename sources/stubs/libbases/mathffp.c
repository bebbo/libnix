/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* MathBase[2] = { (void*)-1, "mathffp.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/mathffp.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * MathBase = NULL;
__attribute__((weak)) struct MathIFace* IMath = NULL;

void __init_Math(void) __attribute__((constructor));
void __exit_Math(void) __attribute__((destructor));

void __init_Math(void) {
  if (MathBase == NULL) {
    MathBase = (struct Library *) IExec->OpenLibrary("mathffp.library", 0);
    assert(MathBase != NULL);
  }
  if (IMath == NULL) {
    IMath = (struct MathIFace*) IExec->GetInterface((struct Library*) MathBase, "main", 1, NULL);
    assert(IMath != NULL);
  }
}

void __exit_Math(void) {
  IExec->DropInterface((struct Interface*) IMath);
  IExec->CloseLibrary((struct Library*) MathBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
