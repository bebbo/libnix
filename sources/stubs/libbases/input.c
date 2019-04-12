/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* InputBase[2] = { 0, "input.device" };
ADD2LIB(InputBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/input.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Device * InputBase = NULL;
__attribute__((weak)) struct InputIFace* IInput = NULL;

void __init_Input(void) __attribute__((constructor));
void __exit_Input(void) __attribute__((destructor));

void __init_Input(void) {
  if (InputBase == NULL) {
    InputBase = (struct Device *) IExec->OpenLibrary("input.device", 0);
    assert(InputBase != NULL);
  }
  if (IInput == NULL) {
    IInput = (struct InputIFace*) IExec->GetInterface((struct Library*) InputBase, "main", 1, NULL);
    assert(IInput != NULL);
  }
}

void __exit_Input(void) {
  IExec->DropInterface((struct Interface*) IInput);
  IExec->CloseLibrary((struct Library*) InputBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
