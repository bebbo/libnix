#include <stdio.h>
#include <stdlib.h> /* If you use normal file I/O,
                       the memory functions don't count that much on memory */
#include <debuglib.h>
#include <errno.h>
#include <proto/exec.h>
#include <exec/lists.h>
#include <exec/nodes.h>
#include <stabs.h>

struct MinList __filelist= /* list of open files (fflush() needs also access) */
{
  (struct MinNode *)&__filelist.mlh_Tail,
  NULL,
  (struct MinNode *)&__filelist.mlh_Head
};

FILE *fopen(const char *filename,const char *mode)
{
  struct filenode *node;
  if((node=(struct filenode *)calloc(1,sizeof(struct filenode)))!=NULL)
  {
    if((node->FILE.buffer=(char *)malloc(BUFSIZ))!=NULL)
    {
      node->FILE.bufsize=BUFSIZ;
      node->FILE.flags|=0x80; /* Buffer is malloc'ed */
      if(freopen(filename,mode,&node->FILE)!=NULL)
      { AddHead((struct List *)&__filelist,(struct Node *)&node->node);
        return &node->FILE; }
      free(node->FILE.buffer);
    }
    else
      errno=ENOMEM;
    free(node);
  }
  else
    errno=ENOMEM;
  return NULL;
}

int fclose(FILE *stream)
{ 
  int retval=0;
  struct filenode *node;
  if(stream==NULL)
  {
#ifdef DEBUG_LIB
    FATALERROR("NULL pointer fclose'd\n");
#endif
    return EOF;
  }
  retval=freopen(NULL,NULL,stream)==NULL?EOF:0;
  if(stream->flags&0x80) /* Free buffer if necessary */
  { free(stream->buffer);
    stream->buffer=NULL; }
  node=(struct filenode *)((struct MinNode *)stream-1);
  Remove((struct Node *)&node->node);
  free(node);
  return retval;
}

void __exitstdfio(void)
{
  struct MinNode *node;
  while((node=__filelist.mlh_Head)->mln_Succ!=NULL)
    fclose(&((struct filenode *)node)->FILE);
}

/* Call our private destructor at cleanup */
ADD2EXIT(__exitstdfio,-20);
