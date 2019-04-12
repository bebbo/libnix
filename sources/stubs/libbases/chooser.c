/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* ChooserBase[2] = { 0, "chooser.library" };
ADD2LIB(ChooserBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/chooser.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * ChooserBase = NULL;
__attribute__((weak)) struct ChooserIFace* IChooser = NULL;

void __init_Chooser(void) __attribute__((constructor));
void __exit_Chooser(void) __attribute__((destructor));

void __init_Chooser(void) {
  if (ChooserBase == NULL) {
    ChooserBase = (struct Library *) IExec->OpenLibrary("chooser.library", 0);
    assert(ChooserBase != NULL);
  }
  if (IChooser == NULL) {
    IChooser = (struct ChooserIFace*) IExec->GetInterface((struct Library*) ChooserBase, "main", 1, NULL);
    assert(IChooser != NULL);
  }
}

void __exit_Chooser(void) {
  IExec->DropInterface((struct Interface*) IChooser);
  IExec->CloseLibrary((struct Library*) ChooserBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
