/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".dlist___LIB_LIST__")))
void* TranslatorBase[2] = { (void*)-1, "translator.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/translator.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * TranslatorBase = NULL;
__attribute__((weak)) struct TranslatorIFace* ITranslator = NULL;

void __init_Translator(void) __attribute__((constructor));
void __exit_Translator(void) __attribute__((destructor));

void __init_Translator(void) {
  if (TranslatorBase == NULL) {
    TranslatorBase = (struct Library *) IExec->OpenLibrary("translator.library", 0);
    assert(TranslatorBase != NULL);
  }
  if (ITranslator == NULL) {
    ITranslator = (struct TranslatorIFace*) IExec->GetInterface((struct Library*) TranslatorBase, "main", 1, NULL);
    assert(ITranslator != NULL);
  }
}

void __exit_Translator(void) {
  IExec->DropInterface((struct Interface*) ITranslator);
  IExec->CloseLibrary((struct Library*) TranslatorBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
