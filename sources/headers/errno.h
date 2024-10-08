#ifndef _ERRNO_H
#define _ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define errno (*__errno)

#ifdef __posix_threads__
extern int * __thread __errno;
#else
extern int * __errno;
#endif

#include <sys/errno.h>

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ERRNO_H */
