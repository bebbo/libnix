/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* FuelGaugeBase = 0;
void ** __getFuelGaugeBase() { return &FuelGaugeBase; }
static void * const __init[2] = { __getFuelGaugeBase, "fuelgauge.library"};
ADD2LIB(__init);
#else
void* FuelGaugeBase[2] = { 0, "fuelgauge.library" };
ADD2LIB(FuelGaugeBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/fuelgauge.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * FuelGaugeBase = NULL;
__attribute__((weak)) struct FuelGaugeIFace* IFuelGauge = NULL;

void __init_FuelGauge(void) __attribute__((constructor));
void __exit_FuelGauge(void) __attribute__((destructor));

void __init_FuelGauge(void) {
  if (FuelGaugeBase == NULL) {
    FuelGaugeBase = (struct Library *) IExec->OpenLibrary("fuelgauge.library", 0);
    assert(FuelGaugeBase != NULL);
  }
  if (IFuelGauge == NULL) {
    IFuelGauge = (struct FuelGaugeIFace*) IExec->GetInterface((struct Library*) FuelGaugeBase, "main", 1, NULL);
    assert(IFuelGauge != NULL);
  }
}

void __exit_FuelGauge(void) {
  IExec->DropInterface((struct Interface*) IFuelGauge);
  IExec->CloseLibrary((struct Library*) FuelGaugeBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
