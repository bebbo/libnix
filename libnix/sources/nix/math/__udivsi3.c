#include "bases.h"

asm("
		.globl	___umodsi3
		.globl	___udivsi3

| D1.L = D0.L % D1.L unsigned

___umodsi3:	moveml	sp@(4:W),d0/d1
		jbsr	___udivsi4
		movel	d1,d0
		rts

| D0.L = D0.L / D1.L unsigned

___udivsi3:	moveml	sp@(4:W),d0/d1
___udivsi4:	movel	"A4(_UtilityBase)",a0
		jmp	a0@(-156:W)
");
