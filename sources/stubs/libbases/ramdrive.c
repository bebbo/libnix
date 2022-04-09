/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* RamdriveDevice = 0;
void ** __getRamdriveDevice() { return &RamdriveDevice; }
static void * __init[2] = { __getRamdriveDevice, "ramdrive.device"};
ADD2LIB(__init);
#else
void* RamdriveDevice[2] = { 0, "ramdrive.device" };
ADD2LIB(RamdriveDevice);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/ramdrive.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Device * RamdriveDevice = NULL;
__attribute__((weak)) struct RamdriveDeviceIFace* IRamdriveDevice = NULL;

void __init_RamdriveDevice(void) __attribute__((constructor));
void __exit_RamdriveDevice(void) __attribute__((destructor));

void __init_RamdriveDevice(void) {
  if (RamdriveDevice == NULL) {
    RamdriveDevice = (struct Device *) IExec->OpenLibrary("ramdrive.device", 0);
    assert(RamdriveDevice != NULL);
  }
  if (IRamdriveDevice == NULL) {
    IRamdriveDevice = (struct RamdriveDeviceIFace*) IExec->GetInterface((struct Library*) RamdriveDevice, "main", 1, NULL);
    assert(IRamdriveDevice != NULL);
  }
}

void __exit_RamdriveDevice(void) {
  IExec->DropInterface((struct Interface*) IRamdriveDevice);
  IExec->CloseLibrary((struct Library*) RamdriveDevice);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
