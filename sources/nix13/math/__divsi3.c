asm(
"		.globl	___modsi3;"
"		.globl	___divsi3;"

/* D1.L = D0.L % D1.L signed */

"___modsi3:"
"	movem.l	sp@(4:W),d0/d1;"
"	jbsr	___divsi4;"
"	move.l	d1,d0;"
"	rts;"

/* D0.L = D0.L / D1.L signed */

"_div:;"
"_ldiv:;"
"___divsi3:	"
"	moveml	sp@(4:W),d0/d1;"
"___divsi4:"
"	tst.l	d0;"
"	bpl		Ld0pos;"
"	neg.l	d0;"
"	tst.l	d1;"
"	bpl		Ld1pos;"
"	neg.l	d1;"
"	jbsr	___udivsi4;"
"	neg.l	d1;"
"	rts;"

"Ld1pos:"
"	jbsr	___udivsi4;"
"	neg.l	d1;"
"	neg.l	d0;"
"	rts;"

"Ld0pos:"
"	tst.l	d1;"
"	bpl	Ld0d1pos;"
"	neg.l	d1;"
"	jbsr	___udivsi4;"
"	neg.l	d0;"
"	rts;"

"Ld0d1pos:"
"	jbra	___udivsi4;"
);
