/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* DiskfontBase = 0;
void ** __getDiskfontBase() { return &DiskfontBase; }
static void * __init[2] = { __getDiskfontBase, "diskfont.library"};
ADD2LIB(__init);
#else
void* DiskfontBase[2] = { 0, "diskfont.library" };
ADD2LIB(DiskfontBase);
#endif

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
