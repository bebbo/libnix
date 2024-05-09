| residentable baserelative startup code for gcc v2.3.3+
| (c) by M.Fleischer and G.Nikl Wed Apr 13 17:46 1994
| No bugs known
|
| Problem: geta4()
| I really don�t know how to implement it with multiple starts
|
| You should use the non-resident startup-code if you need it !

| some specific defines

_LVOForbid	=	-132
_LVOAllocMem	=	-198
_LVOFindTask	=	-294
_LVOFreeMem	=	-210
_LVOGetMsg	=	-372
_LVOReplyMsg	=	-378
_LVOWaitPort	=	-384
_LVOCopyMemQuick =	-630

tc_TrapData =     46
pr_MsgPort	=	  92
pr_CLI		=	 172
ThisTask    =    276
Attn        =    0x128

ERROR_NO_FREE_STORE =	 103

| public symbols

		.globl	_exit
		.globl	__exit
		.text

| first entry - check for cli or wb start

start:
		movel	a0,d3
		movel	d0,d4

		movel	4:W,a6

		movel	a6@(ThisTask:W),a3
		tstl	a3@(pr_CLI:L)
		subal	a2,a2
		bne	fromCLI

| wb start - get our message

fromWB:
	 	lea	a3@(pr_MsgPort:L),a0
		jsr	a6@(_LVOWaitPort:L)
		lea	a3@(pr_MsgPort:L),a0
		jsr	a6@(_LVOGetMsg:L)
		movel	d0,a2

| resident setup - allocate memory and relocate

fromCLI:
| check cpu
		btst.b  #1,1+Attn(a6)
		jne cpuok

| alert
		move.l  #0x68020,d7
		jsr -0x6c(a6)

		moveq.l	#20,d7
		bra		cleanup

cpuok:
		movql	#ERROR_NO_FREE_STORE,d7
		movel	#___data_size,d2
		movel	d2,d0
		movql	#1,d1
		swap	d1
		jsr	a6@(_LVOAllocMem:L)
		movel	d0,a4
		movel	a4,d0
		beq	cleanup
		lea	___a4_init-0x7ffe,a5
		movel	d2,d0
		movel	a5,a0
		movel	a4,a1
		jsr	a6@(_LVOCopyMemQuick:L)
		lea	___datadata_relocs,a0
		movel	a0@+,d0
		beq	no_reloc
		movel	a5,d1
		subl	a4,d1
do_reloc:	movel	a0@+,a1
		subl	d1,a4@(a1:l)
		subql	#1,d0
		bne	do_reloc
no_reloc:	lea	a4@(0x7ffe:L),a4
		movel	a4,tc_TrapData(a3)

		movel	sp,a4@(___SaveSP:L)
		movel	a6,a4@(_SysBase:L)
		movel	a2,a4@(__WBenchMsg:L)
		movel	d3,a4@(___commandline:L)
		movel	d4,a4@(___commandlen:L)
		movel	d2,a4@(___MemLen:L)

| call main() - push args onto stack

		lea	___INIT_LIST__,a2
		addqw	#4,a2
		moveql	#-1,d2
		jbsr	callfuncs
		movel	a4@(___env:L),sp@-
		movel	a4@(___argv:L),sp@-
		movel	a4@(___argc:L),sp@-
		jbsr	_main
		movel	d0,sp@(4:L)

| exit() entry - get return val, restore stackptr

_exit:
__exit:
		movel	(sp)+,a0
		movel	(sp)+,d0
		movel	a4@(___SaveSP:L),sp
		movel	d0,-(sp)
		movel	a0,-(sp)
	 	lea	___EXIT_LIST__,a2
		addqw	#4,a2
		moveql	#0,d2
		jbsr	callfuncs

__Exit: .globl	__Exit
____exit: .globl	____exit
		movel	sp@(4:L),d7
		movel	a4@(___SaveSP:L),sp

| prepare cleanup - setup regs, free resident memory

		movel	a4@(_SysBase:L),a6

		movel	a4@(__WBenchMsg:L),a2
		movel	a4@(___MemLen:L),d0
		lea	a4@(-0x7ffe:L),a1
		jsr	a6@(_LVOFreeMem:L)

| cleanup - reply wbmsg and exit

cleanup:
		movel	a2,d0
		beqs	todos
		jsr	a6@(_LVOForbid:L)
		movel	a2,a1
		jsr	a6@(_LVOReplyMsg:L)
todos:
		movel	d7,d0
		rts

___restore_a4: .globl ___restore_a4
_geta4: 	lea	___a4_init,a4
		movel	4:W,a4
		movel	a4@(ThisTask:W),a4
		movel	tc_TrapData(a4),a4
		rts

| call all functions in the NULL terminated list pointed to by a2
| d2 ascending or descending priority mode

callfuncs:	lea	a4@(cleanupflag:L),a5
		movel	a2,a3
		moveql	#0,d3
		jra	oldpri
stabloop:	movel	a3@+,d4
		movel	a5@,d5
		cmpl	d4,d5
		jne	notnow
		movel	d0,a0
		jsr	a0@
notnow: 	eorl	d2,d4
		eorl	d2,d5
		cmpl	d5,d4
		jcc	oldpri
		cmpl	d3,d4
		jls	oldpri
		movel	d4,d3
oldpri: 	movel	a3@+,d0
		jne	stabloop
		eorl	d2,d3
		movel	d3,a5@
		cmpl	d2,d3
		jne	callfuncs
		rts

		.data

_SysBase:	.globl _SysBase
		.long ___nocommandline
___SaveSP:	.globl ___SaveSP
		.long ___cpucheck
		.long ___initlibraries
		.long ___initcpp

| data area

.comm		__WBenchMsg,4
.comm		___commandline,4
.comm		___commandlen,4
.comm		___MemLen,4
.comm		___argc,4
.comm		___argv,4
.comm		___env,4
.lcomm		cleanupflag,4

	.globl	___LIB_LIST__
	.globl	___INIT_LIST__
	.globl	___EXIT_LIST__
	.globl	___CTOR_LIST__
	.globl	___DTOR_LIST__

.section	.dlist___LIB_LIST__,"aw"
___LIB_LIST__:
		.long 0

.section	.list___INIT_LIST__,"aw"
___INIT_LIST__:
		.long 0

.section	.list___EXIT_LIST__,"aw"
___EXIT_LIST__:
		.long 0

.section	.list___CTOR_LIST__,"aw"
___CTOR_LIST__:
		.long 0

.section	.list___DTOR_LIST__,"aw"
___DTOR_LIST__:
		.long 0

.section	.end_of_lists,"aw"
		.long 0
.section	.end_of_dlists,"aw"
		.long 0
