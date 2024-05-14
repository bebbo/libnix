| not baserelative startup code for gcc v2.3.3+
| (c) by M.Fleischer and G.Nikl Wed Apr 13 17:44 1994
| No bugs known

| some specific defines (disabled to prevent multiple definition - main source = libamiga.a

| _LVOForbid	=	-132
| _LVOFindTask	=	-294
| _LVOGetMsg	=	-372
| _LVOReplyMsg	=	-378
| _LVOWaitPort	=	-384

pr_MsgPort	=	  92
pr_CLI		=	 172
ThisTask    =    276

| public symbols

		.globl _start
		.globl	_exit
		.globl	__exit
		.globl	____exit
		.globl ___main
		.section .text

| first entry - init some vars, check for cli or wb start

_start:		movel	a0,___commandline
		movel	d0,___commandlen

		movel	sp,___SaveSP
		movel	4:W,a6
		movel	a6,_SysBase

		movel	a6@(ThisTask:W),a3
		tstl	a3@(pr_CLI:W)
		bne	fromCLI

| wb start - get wbmsg

fromWB: 	lea	a3@(pr_MsgPort:W),a0
		jsr	a6@(_LVOWaitPort:W)
		lea	a3@(pr_MsgPort:W),a0
		jsr	a6@(_LVOGetMsg:W)
		movel	d0,__WBenchMsg

| execute all init functions then call main

fromCLI:	lea	___INIT_LIST__+4,a2
		moveql	#-1,d2
		jbsr	callfuncs
		movel	___env,sp@-
		movel	___argv,sp@-
		movel	___argc,sp@-
		jsr	_main
		movel	d0,sp@(4:W)

| exit() entry - execute all exit functions, reply wbmsg

_exit:
__exit:
		movel	(sp)+,a0
		movel	(sp)+,d0
		movel	___SaveSP,sp
		movel	d0,-(sp)
		movel	a0,-(sp)
	 	lea	___EXIT_LIST__+4,a2
		moveql	#0,d2
		jbsr	callfuncs

__Exit: .globl	__Exit
____exit: .globl	____exit
		movel	_SysBase,a6
		movel	__WBenchMsg,d2
		beq	todos
		jsr	a6@(_LVOForbid:W)
		movel	d2,a1
		jsr	a6@(_LVOReplyMsg:W)

| leave - get return val, restore stackptr
todos:		movel	sp@(4:W),d0
		movel	___SaveSP,sp
		rts

| call all functions in the NULL terminated list pointed to by a2
| d2 ascending or descending priority mode

callfuncs:	lea	cleanupflag,a5
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
___main:
		rts

		.data

_SysBase:	.globl _SysBase
		.long ___nocommandline
___SaveSP:	.globl ___SaveSP
		.long ___initlibraries
		.long ___initcpp

| data area

.comm		__WBenchMsg,4
.comm		___commandline,4
.comm		___commandlen,4
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
