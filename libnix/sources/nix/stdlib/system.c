#include <utility/tagitem.h>
#include <dos/dos.h>
#include <proto/dos.h>

static struct TagItem list[]={ { TAG_END,0 } }; /* No Tags */

int system(const char *string)
{
  if(string==NULL)
    return 1;
  else
    return SystemTagList((char *)string,list); 
}
