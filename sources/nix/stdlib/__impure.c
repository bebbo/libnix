/**
 * Glue for code built without -noixemul using newlib.
 * At least support errno/stdin/stdout/stderr
 */

// refer to data in __stdio.c
extern int errno;
int * _impure_ptr = &errno;
