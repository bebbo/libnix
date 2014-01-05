#include <dos/dos.h>
#include <utility/tagitem.h>
#include <proto/dos.h>
#include <errno.h>

int system(const char *string)
{ static struct TagItem notags[]={ { TAG_END,0 } };

  if(string == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (((struct Library *)DOSBase)->lib_Version >= 36)
    return SystemTagList((char *)string, notags);
  else
    return (int)~Execute((STRPTR)string, 0l, Output());
}
