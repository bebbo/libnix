/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* LocaleBase[2] = { 0, "locale.library" };
ADD2LIB(LocaleBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <libraries/locale.h>
#include <dos/dos.h>
#include <utility/hooks.h>
#include <utility/tagitem.h>
#include <rexx/storage.h>

#include <interfaces/locale.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct LocaleBase * LocaleBase = NULL;
__attribute__((weak)) struct LocaleIFace* ILocale = NULL;

void __init_Locale(void) __attribute__((constructor));
void __exit_Locale(void) __attribute__((destructor));

void __init_Locale(void) {
  if (LocaleBase == NULL) {
    LocaleBase = (struct LocaleBase *) IExec->OpenLibrary("locale.library", 0);
    assert(LocaleBase != NULL);
  }
  if (ILocale == NULL) {
    ILocale = (struct LocaleIFace*) IExec->GetInterface((struct Library*) LocaleBase, "main", 1, NULL);
    assert(ILocale != NULL);
  }
}

void __exit_Locale(void) {
  IExec->DropInterface((struct Interface*) ILocale);
  IExec->CloseLibrary((struct Library*) LocaleBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
