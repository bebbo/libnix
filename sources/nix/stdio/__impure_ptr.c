#ifdef __posix_threads__
extern void * ___stdin[4];
void **_impure_ptr = &___stdin[0];
#else
extern int errno;
void **_impure_ptr = (void **) (&errno); /* stdin, stdout, stderr */
#endif
