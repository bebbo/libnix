| baserelative startup code for gcc v2.3.3+
| (c) by M.Fleischer and G.Nikl Wed Apr 13 17:45 1994
| No bugs known

| some specific defines

_LVOForbid	=	-132
_LVOFindTask	=	-294
_LVOGetMsg	=	-372
_LVOReplyMsg	=	-378
_LVOWaitPort	=	-384

pr_MsgPort	=	  92
pr_CLI		=	 172
ThisTask    =    276
Attn        =    0x128

| public symbols

		.globl	__exit
		.globl	_geta4
		.global ___restore_a4
		.text

| first entry - init some vars, check for cli or wb start

start:
		movel	4:L,a6
		movel	a6@(ThisTask:W),a3

| wb start - get wbmsg
		moveq.l	#0,d6
		tstl	a3@(pr_CLI:L)
		bne	fromCLI
fromWB:
		lea	a3@(pr_MsgPort:L),a0
		jsr	a6@(_LVOWaitPort:L)
		lea	a3@(pr_MsgPort:L),a0
		jsr	a6@(_LVOGetMsg:L)
		move.l	d0,d6
fromCLI:

| check cpu
		btst.b  #1,1+Attn(a6)
		jne cpuok

| alert
		move.l  #0x68020,d7
		jsr -0x6c(a6)

		moveq.l	#20,d7
		move.l	d6,d2
		bra		cleanup

cpuok:
		movel	#___bss_init_size,d1
		jbsr	_geta4
		beqs	nobss
		lea	a4@(__edata:L),a1
clrbss:
		clrl	a1@+
		subql	#4,d1
		bgts	clrbss

nobss:
		movel	a0,a4@(___commandline:L)
		movel	d0,a4@(___commandlen:L)

		movel	sp,a4@(___SaveSP:L)
		movel	a6,a4@(_SysBase:L)
		movel	d6,a4@(__WBenchMsg:L)

| execute all init functions then call main
		lea	a4@(___INIT_LIST__:L),a2
		addqw	#4,a2
		moveql	#-1,d2
		jbsr	callfuncs
		movel	a4@(___env:L),sp@-
		movel	a4@(___argv:L),sp@-
		movel	a4@(___argc:L),sp@-
		jbsr	_main
		movel	d0,sp@(4:L)

| exit() entry - execute all exit functions, reply wbmsg

__exit:
	 	lea	a4@(___EXIT_LIST__:L),a2
		addqw	#4,a2
		moveql	#0,d2
		jbsr	callfuncs

		movel	a4@(___SaveSP:L),sp
		movel	sp@(4:L),d7

		movel	a4@(_SysBase:L),a6
		movel	a4@(__WBenchMsg:L),d2
cleanup:
		beq	todos
		jsr	a6@(_LVOForbid:L)
		movel	d2,a1
		jsr	a6@(_LVOReplyMsg:L)

| leave - get return val, restore stackptr

todos:
		move.l	d7,d0
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

| get baseptr

___restore_a4:		
_geta4: 	lea	___a4_init,a4
		rts

| redirection of _exit

		.stabs	"_exit",11,0,0,0
		.stabs	"__exit",1,0,0,0

| data area

		.data

		.long ___nocommandline
		.long ___cpucheck

.comm		_SysBase,4
.comm		___SaveSP,4
.comm		__WBenchMsg,4
.comm		___commandline,4
.comm		___commandlen,4
.comm		___argc,4
.comm		___argv,4
.comm		___env,4
.lcomm		cleanupflag,4
