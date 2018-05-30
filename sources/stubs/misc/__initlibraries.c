#include <proto/exec.h>
#include "stabs.h"
#include <stdio.h>
#include <string.h>

extern struct lib /* These are the elements pointed to by __LIB_LIST__ */
{ struct Library *base;
  char *name;
} *__LIB_LIST__[];

extern void __request(const char *text);
extern void exit(int returncode);

static void __openliberror(ULONG,char const *);

static void __openliberror(ULONG version, char const * ln)
{
  char buf[60];
  strcpy(buf, "can't load ");
  strcat(buf, ln);
  strcat(buf, "\n");
  fputs(stderr, buf);
  exit(20);
}

void __initlibraries(void)
{
  struct lib **list=__LIB_LIST__;
  ULONG numbases=(ULONG)*list++;

  if(numbases)
    do {
      struct lib *l=*list++;
      if((l->base=OpenLibrary(l->name,0))==NULL)
        __openliberror(0,l->name);
    } while(--numbases);
}

void __exitlibraries(void)
{
  struct lib **list=__LIB_LIST__;
  ULONG numbases=(ULONG)*list++;

  if(numbases)
    do {
      struct lib *l=*list++;
      struct Library *lb=l->base;
      if(lb!=NULL) {
        /* l->base=NULL; */
        CloseLibrary(lb);
      }
    } while(--numbases);
}

ADD2INIT(__initlibraries,-60);
ADD2EXIT(__exitlibraries,-60);
