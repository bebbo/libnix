/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* ConsoleDevice = 0;
void ** __getConsoleDevice() { return &ConsoleDevice; }
static void * __init[2] = { __getConsoleDevice, "console.device"};
ADD2LIB(__init);
#else
void* ConsoleDevice[2] = { 0, "console.device" };
ADD2LIB(ConsoleDevice);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/libraries.h>
#include <devices/inputevent.h>
#include <devices/keymap.h>

#include <interfaces/console.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Device * ConsoleDevice = NULL;
__attribute__((weak)) struct ConsoleDeviceIFace* IConsoleDevice = NULL;

void __init_ConsoleDevice(void) __attribute__((constructor));
void __exit_ConsoleDevice(void) __attribute__((destructor));

void __init_ConsoleDevice(void) {
  if (ConsoleDevice == NULL) {
    ConsoleDevice = (struct Device *) IExec->OpenLibrary("console.device", 0);
    assert(ConsoleDevice != NULL);
  }
  if (IConsoleDevice == NULL) {
    IConsoleDevice = (struct ConsoleDeviceIFace*) IExec->GetInterface((struct Library*) ConsoleDevice, "main", 1, NULL);
    assert(IConsoleDevice != NULL);
  }
}

void __exit_ConsoleDevice(void) {
  IExec->DropInterface((struct Interface*) IConsoleDevice);
  IExec->CloseLibrary((struct Library*) ConsoleDevice);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
