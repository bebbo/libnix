/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* AmlBase = 0;
void ** __getAmlBase() { return &AmlBase; }
static void * __init[2] = { __getAmlBase, "aml.library"};
ADD2LIB(__init);
#else
void* AmlBase[2] = { 0, "aml.library" };
ADD2LIB(AmlBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <utility/tagitem.h>
#include <utility/hooks.h>
#include <rexx/storage.h>
#include <libraries/aml.h>

#include <interfaces/aml.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * AmlBase = NULL;
__attribute__((weak)) struct AmlIFace* IAml = NULL;

void __init_Aml(void) __attribute__((constructor));
void __exit_Aml(void) __attribute__((destructor));

void __init_Aml(void) {
  if (AmlBase == NULL) {
    AmlBase = (struct Library *) IExec->OpenLibrary("aml.library", 0);
    assert(AmlBase != NULL);
  }
  if (IAml == NULL) {
    IAml = (struct AmlIFace*) IExec->GetInterface((struct Library*) AmlBase, "main", 1, NULL);
    assert(IAml != NULL);
  }
}

void __exit_Aml(void) {
  IExec->DropInterface((struct Interface*) IAml);
  IExec->CloseLibrary((struct Library*) AmlBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
