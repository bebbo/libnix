/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* DiskfontBase[2] = { 0, "diskfont.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <dos/dos.h>
#include <libraries/diskfont.h>
#include <utility/tagitem.h>

#include <interfaces/diskfont.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * DiskfontBase = NULL;
__attribute__((weak)) struct DiskfontIFace* IDiskfont = NULL;

void __init_Diskfont(void) __attribute__((constructor));
void __exit_Diskfont(void) __attribute__((destructor));

void __init_Diskfont(void) {
  if (DiskfontBase == NULL) {
    DiskfontBase = (struct Library *) IExec->OpenLibrary("diskfont.library", 0);
    assert(DiskfontBase != NULL);
  }
  if (IDiskfont == NULL) {
    IDiskfont = (struct DiskfontIFace*) IExec->GetInterface((struct Library*) DiskfontBase, "main", 1, NULL);
    assert(IDiskfont != NULL);
  }
}

void __exit_Diskfont(void) {
  IExec->DropInterface((struct Interface*) IDiskfont);
  IExec->CloseLibrary((struct Library*) DiskfontBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
