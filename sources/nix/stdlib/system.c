#include <dos/dos.h>
#include <utility/tagitem.h>
#include <proto/dos.h>
#include <errno.h>

int system(const char *string)
{
  if(string == NULL) {
    errno = EINVAL;
    return -1;
  }
#ifndef __KICK13__
  if (((struct Library *)DOSBase)->lib_Version >= 36) {
	static struct TagItem notags[]={ { TAG_END,0 } };
    return SystemTagList((char *)string, notags);
  }
  else
#endif
    return (int)~Execute((STRPTR)string, 0l, Output());
}
