/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* StringBase = 0;
void ** __getStringBase() { return &StringBase; }
static void * __init[2] = { __getStringBase, "string.library"};
ADD2LIB(__init);
#else
void* StringBase[2] = { 0, "string.library" };
ADD2LIB(StringBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/string.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * StringBase = NULL;
__attribute__((weak)) struct StringIFace* IString = NULL;

void __init_String(void) __attribute__((constructor));
void __exit_String(void) __attribute__((destructor));

void __init_String(void) {
  if (StringBase == NULL) {
    StringBase = (struct Library *) IExec->OpenLibrary("string.library", 0);
    assert(StringBase != NULL);
  }
  if (IString == NULL) {
    IString = (struct StringIFace*) IExec->GetInterface((struct Library*) StringBase, "main", 1, NULL);
    assert(IString != NULL);
  }
}

void __exit_String(void) {
  IExec->DropInterface((struct Interface*) IString);
  IExec->CloseLibrary((struct Library*) StringBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
