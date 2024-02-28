/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* SpeedBarBase[2] = { (void*)-1, "gadgets/speedbar.gadget" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/speedbar.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * SpeedBarBase = NULL;
__attribute__((weak)) struct SpeedBarIFace* ISpeedBar = NULL;

void __init_SpeedBar(void) __attribute__((constructor));
void __exit_SpeedBar(void) __attribute__((destructor));

void __init_SpeedBar(void) {
  if (SpeedBarBase == NULL) {
    SpeedBarBase = (struct Library *) IExec->OpenLibrary("speedbar.library", 0);
    assert(SpeedBarBase != NULL);
  }
  if (ISpeedBar == NULL) {
    ISpeedBar = (struct SpeedBarIFace*) IExec->GetInterface((struct Library*) SpeedBarBase, "main", 1, NULL);
    assert(ISpeedBar != NULL);
  }
}

void __exit_SpeedBar(void) {
  IExec->DropInterface((struct Interface*) ISpeedBar);
  IExec->CloseLibrary((struct Library*) SpeedBarBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
