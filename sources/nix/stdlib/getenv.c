#include <stdlib.h>
#include <dos/dos.h>
#include <dos/var.h>
#include <proto/dos.h>

#ifndef GVF_BINARY_VAR
#define GVF_BINARY_VAR 0x400
#endif

char *getenv(const char *name)
{ static char *var=NULL;
  size_t len,i=0;
  do
  { i+=64;
    if(var!=NULL) /* free old buffer */
      free(var);
    var=malloc(i); /* and get a new one */
    if(var==NULL) /* Oh, dear */
      return NULL;
    len=GetVar((char *)name,var,i,GVF_BINARY_VAR)+1;
  }while(len>=i); /* just to be sure we got everything, we _require_ 1 unused byte */
  if(len!=0) /* Variable does exist */
    return var;
  if((name[0]=='H'||name[0]=='h')
    && (name[1]=='O'||name[1]=='o')
    && (name[2]=='M'||name[2]=='m')
    && (name[3]=='E'||name[3]=='e') && !name[4])
    {
      return("SYS:Prefs/Env-Archive");
    }
  return NULL;
}
