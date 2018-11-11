#ifndef __FILENODE_H__
#define __FILENODE_H__
/* objects in __filelist */
#include <exec/lists.h>
struct filenode {
  struct MinNode node;
  FILE theFILE;
};
#endif // __FILENODE_H__
