/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* ARexxBase[2] = { 0, "arexx.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/arexx.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * ARexxBase = NULL;
__attribute__((weak)) struct ARexxIFace* IARexx = NULL;

void __init_ARexx(void) __attribute__((constructor));
void __exit_ARexx(void) __attribute__((destructor));

void __init_ARexx(void) {
  if (ARexxBase == NULL) {
    ARexxBase = (struct Library *) IExec->OpenLibrary("arexx.library", 0);
    assert(ARexxBase != NULL);
  }
  if (IARexx == NULL) {
    IARexx = (struct ARexxIFace*) IExec->GetInterface((struct Library*) ARexxBase, "main", 1, NULL);
    assert(IARexx != NULL);
  }
}

void __exit_ARexx(void) {
  IExec->DropInterface((struct Interface*) IARexx);
  IExec->CloseLibrary((struct Library*) ARexxBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
