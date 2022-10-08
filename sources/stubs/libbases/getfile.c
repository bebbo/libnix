/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* GetFileBase[2] = { 0, "getfile.library" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/getfile.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * GetFileBase = NULL;
__attribute__((weak)) struct GetFileIFace* IGetFile = NULL;

void __init_GetFile(void) __attribute__((constructor));
void __exit_GetFile(void) __attribute__((destructor));

void __init_GetFile(void) {
  if (GetFileBase == NULL) {
    GetFileBase = (struct Library *) IExec->OpenLibrary("getfile.library", 0);
    assert(GetFileBase != NULL);
  }
  if (IGetFile == NULL) {
    IGetFile = (struct GetFileIFace*) IExec->GetInterface((struct Library*) GetFileBase, "main", 1, NULL);
    assert(IGetFile != NULL);
  }
}

void __exit_GetFile(void) {
  IExec->DropInterface((struct Interface*) IGetFile);
  IExec->CloseLibrary((struct Library*) GetFileBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
