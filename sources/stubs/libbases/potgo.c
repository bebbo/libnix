/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* PotgoBase = 0;
void ** __getPotgoBase() { return &PotgoBase; }
static void * __init[2] = { __getPotgoBase, "potgo.resource"};
ADD2LIB(__init);
#else
void* PotgoBase[2] = { 0, "potgo.resource" };
ADD2LIB(PotgoBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>

#include <interfaces/potgo.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * PotgoBase = NULL;
__attribute__((weak)) struct PotgoIFace* IPotgo = NULL;

void __init_Potgo(void) __attribute__((constructor));
void __exit_Potgo(void) __attribute__((destructor));

void __init_Potgo(void) {
  if (PotgoBase == NULL) {
    PotgoBase = (struct Library *) IExec->OpenLibrary("potgo.resource", 0);
    assert(PotgoBase != NULL);
  }
  if (IPotgo == NULL) {
    IPotgo = (struct PotgoIFace*) IExec->GetInterface((struct Library*) PotgoBase, "main", 1, NULL);
    assert(IPotgo != NULL);
  }
}

void __exit_Potgo(void) {
  IExec->DropInterface((struct Interface*) IPotgo);
  IExec->CloseLibrary((struct Library*) PotgoBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
