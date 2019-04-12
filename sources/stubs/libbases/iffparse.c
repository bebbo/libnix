/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* IFFParseBase[2] = { 0, "iffparse.library" };
ADD2LIB(IFFParseBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <libraries/iffparse.h>
#include <utility/hooks.h>

#include <interfaces/iffparse.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * IFFParseBase = NULL;
__attribute__((weak)) struct IFFParseIFace* IIFFParse = NULL;

void __init_IFFParse(void) __attribute__((constructor));
void __exit_IFFParse(void) __attribute__((destructor));

void __init_IFFParse(void) {
  if (IFFParseBase == NULL) {
    IFFParseBase = (struct Library *) IExec->OpenLibrary("iffparse.library", 0);
    assert(IFFParseBase != NULL);
  }
  if (IIFFParse == NULL) {
    IIFFParse = (struct IFFParseIFace*) IExec->GetInterface((struct Library*) IFFParseBase, "main", 1, NULL);
    assert(IIFFParse != NULL);
  }
}

void __exit_IFFParse(void) {
  IExec->DropInterface((struct Interface*) IIFFParse);
  IExec->CloseLibrary((struct Library*) IFFParseBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
