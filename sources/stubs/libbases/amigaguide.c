/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* AmigaGuideBase[2] = { 0, "amigaguide.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <exec/ports.h>
#include <dos/dos.h>
#include <libraries/amigaguide.h>
#include <utility/tagitem.h>
#include <utility/hooks.h>
#include <rexx/storage.h>

#include <interfaces/amigaguide.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * AmigaGuideBase = NULL;
__attribute__((weak)) struct AmigaGuideIFace* IAmigaGuide = NULL;

void __init_AmigaGuide(void) __attribute__((constructor));
void __exit_AmigaGuide(void) __attribute__((destructor));

void __init_AmigaGuide(void) {
  if (AmigaGuideBase == NULL) {
    AmigaGuideBase = (struct Library *) IExec->OpenLibrary("amigaguide.library", 0);
    assert(AmigaGuideBase != NULL);
  }
  if (IAmigaGuide == NULL) {
    IAmigaGuide = (struct AmigaGuideIFace*) IExec->GetInterface((struct Library*) AmigaGuideBase, "main", 1, NULL);
    assert(IAmigaGuide != NULL);
  }
}

void __exit_AmigaGuide(void) {
  IExec->DropInterface((struct Interface*) IAmigaGuide);
  IExec->CloseLibrary((struct Library*) AmigaGuideBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
