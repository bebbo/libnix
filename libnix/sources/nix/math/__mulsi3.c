#include "bases.h"

asm("
		.globl	___mulsi3

| D0 = D0 * D1

___mulsi3:	moveml	sp@(4),d0/d1
		movel	"A4(_UtilityBase)",a0
		jmp	a0@(-138:W)
");
