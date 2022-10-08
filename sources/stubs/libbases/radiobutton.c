/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* RadioButtonBase[2] = { 0, "radiobutton.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/radiobutton.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * RadioButtonBase = NULL;
__attribute__((weak)) struct RadioButtonIFace* IRadioButton = NULL;

void __init_RadioButton(void) __attribute__((constructor));
void __exit_RadioButton(void) __attribute__((destructor));

void __init_RadioButton(void) {
  if (RadioButtonBase == NULL) {
    RadioButtonBase = (struct Library *) IExec->OpenLibrary("radiobutton.library", 0);
    assert(RadioButtonBase != NULL);
  }
  if (IRadioButton == NULL) {
    IRadioButton = (struct RadioButtonIFace*) IExec->GetInterface((struct Library*) RadioButtonBase, "main", 1, NULL);
    assert(IRadioButton != NULL);
  }
}

void __exit_RadioButton(void) {
  IExec->DropInterface((struct Interface*) IRadioButton);
  IExec->CloseLibrary((struct Library*) RadioButtonBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
