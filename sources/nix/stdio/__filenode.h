#ifndef __FILENODE_H__
#define __FILENODE_H__
/* objects in ___filelist */
#include <exec/lists.h>
struct filenode {
  struct MinNode node;
  FILE theFILE;
};

/* own stuff */
extern struct MinList ___filelist; /* List of all fopen'ed files */
extern struct MinList __memorylist; /* List of memory puddles */

#endif // __FILENODE_H__
