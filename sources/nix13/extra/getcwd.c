# include <errno.h>
# include <stdint.h>
# include <stdlib.h>

# include <proto/dos.h>

/* getcwd() for Kickstart 1.3 that attempts to follow POSIX spec
 * Features:
 *   - error checking, no extra allocations, no recursion, O(n)
 *
 * We start from the current directory and walk up to the root.
 * Imagine we are in MyPath:MyDir/MySubDir
 * We obtain a FileInfoBlock to MySubDir, then MyDir then MyPath.
 * To avoid allocating extra stuff, holding multiple locks, recursing, etc.
 * we write out all the names as we encounter them in reverse.
 * Example:
 * - obtain a lock to MySubDir, write out riDbuSyM
 * - obtain a lock to MyDir, append /riDyM
 * - obtain a lock to MyPath, append :htaPyM
 * Now we have: riDbuSyM/riDyM:htaPyM
 * then we reverse the string at the end:
 * MyPath:MyDir/MySubDir
 * This requires no extra memory bookkeeping or recursion.
 */
char *getcwd(char *buf, size_t size) {
  if (!size) return errno = EINVAL, NULL;

  char *mybuf = NULL;
  if (!buf && !(mybuf = buf = (char *) malloc(size)))
    return errno = ENOMEM, NULL;

  BPTR dirlock = Lock("", ACCESS_READ);
  if (!dirlock) { errno = ENOENT; goto fail; }

  char *out = buf;
  *out = 0;

  size_t out_size = 0;
  do {
    struct FileInfoBlock fib;
    if (!Examine(dirlock, &fib)) { errno = EIO; goto fail; }

    {
      BPTR new_dirlock = ParentDir(dirlock);
      UnLock(dirlock);
      dirlock = new_dirlock;
    }

    /* Prepend '/' to path except in following cases:
       - if dirlock is 0, we are at the last element (root directory)
       - if out_size is 0, we are at the first element */
    if (out_size && dirlock) *out++ = '/';

    /* Walk a pointer endname to the end of the file name */
    char *name = fib.fib_FileName, *endname = name;
    while (*endname++) {}
    uint16_t name_len = --endname - name;

    /* Some environments (vamos) will already have ':' added to the root dir */
    const int needs_colon = !dirlock && (!name_len || endname[-1] != ':');

    /* Determine if we have enough space to store the path */
    out_size += name_len + needs_colon;
    if (out_size >= size) { errno = ERANGE; goto fail; }

    if (needs_colon)
      *out++ = ':';

    /* Write out the path component in reverse */
    while (name_len--)
      *out++ = *--endname;
  } while (dirlock);

  /* Terminate the string */
  *out = 0;

  /* Reverse the output and we are done */
  for (char *rev = buf; rev < out;) {
    char t = *--out;
    *out = *rev;
    *rev++ = t;
  }

  return buf;
 fail:
  free(mybuf);
  UnLock(dirlock);
  return NULL;
}
