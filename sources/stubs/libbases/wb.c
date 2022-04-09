/* Automatically generated header (sfdc 1.11d)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
#ifdef __baserel__
void* WorkbenchBase = 0;
void ** __getWorkbenchBase() { return &WorkbenchBase; }
static void * __init[2] = { __getWorkbenchBase, "workbench.library"};
ADD2LIB(__init);
#else
void* WorkbenchBase[2] = { 0, "workbench.library" };
ADD2LIB(WorkbenchBase);
#endif

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <dos/dos.h>
#include <workbench/workbench.h>
#include <intuition/intuition.h>
#include <utility/tagitem.h>

#include <interfaces/wb.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * WorkbenchBase = NULL;
__attribute__((weak)) struct WorkbenchIFace* IWorkbench = NULL;

void __init_Workbench(void) __attribute__((constructor));
void __exit_Workbench(void) __attribute__((destructor));

void __init_Workbench(void) {
  if (WorkbenchBase == NULL) {
    WorkbenchBase = (struct Library *) IExec->OpenLibrary("workbench.library", 0);
    assert(WorkbenchBase != NULL);
  }
  if (IWorkbench == NULL) {
    IWorkbench = (struct WorkbenchIFace*) IExec->GetInterface((struct Library*) WorkbenchBase, "main", 1, NULL);
    assert(IWorkbench != NULL);
  }
}

void __exit_Workbench(void) {
  IExec->DropInterface((struct Interface*) IWorkbench);
  IExec->CloseLibrary((struct Library*) WorkbenchBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
