/* Automatically generated header (sfdc 1.11e)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

__attribute__((section(".list___LIB_LIST__")))
void* DiskBase[2] = { 0, "disk.resource" };

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <resources/disk.h>

#include <interfaces/disk.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct DiskResource * DiskBase = NULL;
__attribute__((weak)) struct DiskIFace* IDisk = NULL;

void __init_Disk(void) __attribute__((constructor));
void __exit_Disk(void) __attribute__((destructor));

void __init_Disk(void) {
  if (DiskBase == NULL) {
    DiskBase = (struct DiskResource *) IExec->OpenLibrary("disk.resource", 0);
    assert(DiskBase != NULL);
  }
  if (IDisk == NULL) {
    IDisk = (struct DiskIFace*) IExec->GetInterface((struct Library*) DiskBase, "main", 1, NULL);
    assert(IDisk != NULL);
  }
}

void __exit_Disk(void) {
  IExec->DropInterface((struct Interface*) IDisk);
  IExec->CloseLibrary((struct Library*) DiskBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
