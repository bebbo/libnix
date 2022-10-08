/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* TextFieldBase[2] = { 0, "texteditor.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/texteditor.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * TextFieldBase = NULL;
__attribute__((weak)) struct TextFieldIFace* ITextField = NULL;

void __init_TextField(void) __attribute__((constructor));
void __exit_TextField(void) __attribute__((destructor));

void __init_TextField(void) {
  if (TextFieldBase == NULL) {
    TextFieldBase = (struct Library *) IExec->OpenLibrary("texteditor.library", 0);
    assert(TextFieldBase != NULL);
  }
  if (ITextField == NULL) {
    ITextField = (struct TextFieldIFace*) IExec->GetInterface((struct Library*) TextFieldBase, "main", 1, NULL);
    assert(ITextField != NULL);
  }
}

void __exit_TextField(void) {
  IExec->DropInterface((struct Interface*) ITextField);
  IExec->CloseLibrary((struct Library*) TextFieldBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
