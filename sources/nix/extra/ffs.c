
#include <stdlib.h>

int ffs(int word)
{
  register int i = 0;

  if(word) do {
  
  } while(!((1 << i++) & word));
  
  return i;
}
