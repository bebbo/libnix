/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* LabelBase[2] = { 0, "label.library" };
ADD2LIB(LabelBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/label.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * LabelBase = NULL;
__attribute__((weak)) struct LabelIFace* ILabel = NULL;

void __init_Label(void) __attribute__((constructor));
void __exit_Label(void) __attribute__((destructor));

void __init_Label(void) {
  if (LabelBase == NULL) {
    LabelBase = (struct Library *) IExec->OpenLibrary("label.library", 0);
    assert(LabelBase != NULL);
  }
  if (ILabel == NULL) {
    ILabel = (struct LabelIFace*) IExec->GetInterface((struct Library*) LabelBase, "main", 1, NULL);
    assert(ILabel != NULL);
  }
}

void __exit_Label(void) {
  IExec->DropInterface((struct Interface*) ILabel);
  IExec->CloseLibrary((struct Library*) LabelBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
