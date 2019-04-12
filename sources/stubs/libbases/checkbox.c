/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* CheckBoxBase[2] = { 0, "checkbox.library" };
ADD2LIB(CheckBoxBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/checkbox.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * CheckBoxBase = NULL;
__attribute__((weak)) struct CheckBoxIFace* ICheckBox = NULL;

void __init_CheckBox(void) __attribute__((constructor));
void __exit_CheckBox(void) __attribute__((destructor));

void __init_CheckBox(void) {
  if (CheckBoxBase == NULL) {
    CheckBoxBase = (struct Library *) IExec->OpenLibrary("checkbox.library", 0);
    assert(CheckBoxBase != NULL);
  }
  if (ICheckBox == NULL) {
    ICheckBox = (struct CheckBoxIFace*) IExec->GetInterface((struct Library*) CheckBoxBase, "main", 1, NULL);
    assert(ICheckBox != NULL);
  }
}

void __exit_CheckBox(void) {
  IExec->DropInterface((struct Interface*) ICheckBox);
  IExec->CloseLibrary((struct Library*) CheckBoxBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
