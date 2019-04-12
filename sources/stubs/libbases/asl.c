/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* AslBase[2] = { 0, "asl.library" };
ADD2LIB(AslBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <utility/tagitem.h>
#include <libraries/asl.h>

#include <interfaces/asl.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * AslBase = NULL;
__attribute__((weak)) struct AslIFace* IAsl = NULL;

void __init_Asl(void) __attribute__((constructor));
void __exit_Asl(void) __attribute__((destructor));

void __init_Asl(void) {
  if (AslBase == NULL) {
    AslBase = (struct Library *) IExec->OpenLibrary("asl.library", 0);
    assert(AslBase != NULL);
  }
  if (IAsl == NULL) {
    IAsl = (struct AslIFace*) IExec->GetInterface((struct Library*) AslBase, "main", 1, NULL);
    assert(IAsl != NULL);
  }
}

void __exit_Asl(void) {
  IExec->DropInterface((struct Interface*) IAsl);
  IExec->CloseLibrary((struct Library*) AslBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
