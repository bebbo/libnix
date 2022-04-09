/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* IntegerBase = 0;
void ** __getIntegerBase() { return &IntegerBase; }
static void * __init[2] = { __getIntegerBase, "integer.library"};
ADD2LIB(__init);
#else
void* IntegerBase[2] = { 0, "integer.library" };
ADD2LIB(IntegerBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <intuition/intuition.h>
#include <intuition/classes.h>

#include <interfaces/integer.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * IntegerBase = NULL;
__attribute__((weak)) struct IntegerIFace* IInteger = NULL;

void __init_Integer(void) __attribute__((constructor));
void __exit_Integer(void) __attribute__((destructor));

void __init_Integer(void) {
  if (IntegerBase == NULL) {
    IntegerBase = (struct Library *) IExec->OpenLibrary("integer.library", 0);
    assert(IntegerBase != NULL);
  }
  if (IInteger == NULL) {
    IInteger = (struct IntegerIFace*) IExec->GetInterface((struct Library*) IntegerBase, "main", 1, NULL);
    assert(IInteger != NULL);
  }
}

void __exit_Integer(void) {
  IExec->DropInterface((struct Interface*) IInteger);
  IExec->CloseLibrary((struct Library*) IntegerBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
