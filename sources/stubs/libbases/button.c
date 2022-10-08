/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* ButtonBase[2] = { 0, "button.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/button.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * ButtonBase = NULL;
__attribute__((weak)) struct ButtonIFace* IButton = NULL;

void __init_Button(void) __attribute__((constructor));
void __exit_Button(void) __attribute__((destructor));

void __init_Button(void) {
  if (ButtonBase == NULL) {
    ButtonBase = (struct Library *) IExec->OpenLibrary("button.library", 0);
    assert(ButtonBase != NULL);
  }
  if (IButton == NULL) {
    IButton = (struct ButtonIFace*) IExec->GetInterface((struct Library*) ButtonBase, "main", 1, NULL);
    assert(IButton != NULL);
  }
}

void __exit_Button(void) {
  IExec->DropInterface((struct Interface*) IButton);
  IExec->CloseLibrary((struct Library*) ButtonBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
