/* Automatically generated header (sfdc 1.11)! Do not edit! */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined (__libnix__)

#include <stabs.h>
void* DataTypesBase[2] = { 0, "datatypes.library" };
ADD2LIB(DataTypesBase);

#elif defined (__AMIGAOS4__)

#undef __USE_INLINE__
#define _NO_INLINE
#include <exec/types.h>
#include <exec/lists.h>
#include <intuition/intuition.h>
#include <intuition/classes.h>
#include <intuition/classusr.h>
#include <intuition/gadgetclass.h>
#include <utility/tagitem.h>
#include <datatypes/datatypesclass.h>
#include <datatypes/datatypes.h>
#include <rexx/storage.h>

#include <interfaces/datatypes.h>
#include <proto/exec.h>
#include <assert.h>

__attribute__((weak)) struct Library * DataTypesBase = NULL;
__attribute__((weak)) struct DataTypesIFace* IDataTypes = NULL;

void __init_DataTypes(void) __attribute__((constructor));
void __exit_DataTypes(void) __attribute__((destructor));

void __init_DataTypes(void) {
  if (DataTypesBase == NULL) {
    DataTypesBase = (struct Library *) IExec->OpenLibrary("datatypes.library", 0);
    assert(DataTypesBase != NULL);
  }
  if (IDataTypes == NULL) {
    IDataTypes = (struct DataTypesIFace*) IExec->GetInterface((struct Library*) DataTypesBase, "main", 1, NULL);
    assert(IDataTypes != NULL);
  }
}

void __exit_DataTypes(void) {
  IExec->DropInterface((struct Interface*) IDataTypes);
  IExec->CloseLibrary((struct Library*) DataTypesBase);
}


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */
