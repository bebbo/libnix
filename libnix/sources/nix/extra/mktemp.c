#include <unistd.h>
#include <proto/exec.h>

char *mktemp(char *buf)
{ long pid = (long)FindTask(0L);
  char *c = buf;

  while(*c++); --c;

  while(*--c == 'X') {
    *c = pid % 10 + '0';
    pid /= 10;
  }

  if (++c,*c) {
    for(*c='A'; *c <= 'Z'; (*c)++) {
      if (access(buf,0)) {
        return buf;
      }
    }
    *c = 0;
  }

  return buf;
}
