#include <stdio.h>

asm("\t.bss");
asm("____stdin: .globl ____stdin");
asm("___errno__data: .globl ___errno__data");
asm("__impure_ptr__data: .globl __impure_ptr__data");
asm("\t.long 0");
asm("___sF__data: .globl ___sF__data");
asm("\t.long 0");
asm("\t.long 0");
asm("\t.long 0");

extern FILE * __sF__data[3];
extern int __errno__data;

int * __errno = &__errno__data;
FILE **__sF = &__sF__data[0];
