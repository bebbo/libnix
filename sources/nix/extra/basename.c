#include <proto/dos.h>

char *basename(char *path)
{
  return((char *)FilePart(path));
}
