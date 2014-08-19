/*
 *  TOPPERS/OSEK Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      OSEK Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2006 by Witz Corporation, JAPAN
 * 
 *  上記著作権者は，以下の (1)～(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 *
 *  This program is covered by the TOPPERS License as published
 *  by the  TOPPERS PROJECT (http://www.toppers.jp/en/index.html).
 * 
 */

/*	プロセッサ依存モジュール アセンブリ言語部（AT91SAM7S用） */
/*   Processor Dependent Module (for AT91SAM7S)
 *
 *    Copyright (C) 2007  Masaaki Mizuno 
 *    Department of Computing and Information Sciences,
 *    Kansas State University  (masaaki@cis.ksu.edu)
*/
 
#define _MACRO_ONLY

	.extern debug1
	.extern debug2
/*	外部参照宣言 */
	.extern	runtsk
	.extern	schedtsk
	.extern	tcxb_pc
	.extern	tcxb_sp
	.extern	tinib_task
	.extern	callevel
	.extern	runisr
	.extern	tinib_exepri
	.extern	tcb_curpri
	.extern	call_pretaskhook
	.extern	call_posttaskhook
	.extern	PreTaskHook
	.extern	PostTaskHook
	.extern	lock_flag
	.extern	__system_stack__
	.extern	tcxb_lr
	.extern	tcxb_spsr

/*	外部公開宣言 */
	.global	dispatch
	.type dispatch, %function
	
	.global	start_dispatch
	.type start_dispatch, %function
	
	.global	exit_and_dispatch
	.type exit_and_dispatch, %function
	
	.global	activate_r
	
	.global	_interrupt
	.type _interrupt, %function
	
	.global	dispatch_r
	
	.global	disable_int
	.type disable_int, %function
	
	.global	enable_int
	.type enable_int, %function
	
	.global	nop
	.type nop, %function
	
	.global int_return
	.type int_return, %function

	.text
	.code	32
	.align	4

/////////////////////////////////////////////////////////////////////////////////////////////////
//   dispatch:
//      this function is called by a task
//            save the non-distructive registers (r4-r11, lr)
//            save sp in the sp saving area in TCB
//            save "dispatcher_r" in the pc saving area in TCB
//            jump to "dispatcher"
/////////////////////////////////////////////////////////////////////////////////////////////////
.func dispatch
dispatch:
	stmfd	sp!, {r4-r11, lr} 		//  save the non-distructive registers
	ldr	r0, =tcxb_sp			//  save sp in the sp saving area in TCB
	ldr	r1, =runtsk
	ldrb	r1, [r1]			// "ldrb" performs zero-extension
	str	sp, [r0, r1, asl #2]		// tcxb_sp[runtsk] = sp
	
	ldr	r2, =dispatcher_r		// save "dispatcher_r" in the pc saving area in TCB
	ldr	r0, =tcxb_pc
	str	r2, [r0, r1, asl #2]		// tcxb_pc[runtsk] = "dispatcher_r"
	b	dispatcher			// jump to "dispatcher"
.endfunc

.align	4
////////////////////////////////////////////////////////////////////////////////////////////////
//      dispacth_r:
//          If a task relinquishes the CPU through "dispatch",  
//          it executes this function to be dispatched when it is scheduled again.
//              restore the non-desctructive registers (r4-r11)
//              restore the value of LR (the address  to return from "dispatch") in PC
////////////////////////////////////////////////////////////////////////////////////////////////
dispatcher_r:
	ldmfd	sp!, {r4-r11}
	ldmfd	sp!, {r0}			// the return address  is found abovce the destructive registers in the stack
	bx	r0				//. jump to the address
	
.align	4
////////////////////////////////////////////////////////////////////////////////////////////////
//   activate_r:
//       When a task is scheduled and dispatched for the first time, this function is called
//      Address "activare_r" is set to the PC saving area in TCB by activate_context( ) in cpu_context.h
//           set tinib_exepri[runtsk] to   tcb_curpri[runtsk], where runtsk is the ID of the task to be dispatched
//           enabe interrupt
//           jump to tinib_task[runtsk]
/////////////////////////////////////////////////////////////////////////////////////////////////          
activate_r:
	ldr	r0, =tinib_exepri		// tcb_curpri[runtsk] = tinib_exepri[runtsk]
	ldr	r1, =runtsk
	ldrb 	r1, [r1]
	ldrb	r0, [r0, r1]			// r0 <- tinib_exepri[runtsk]

	ldr	r2, =tcb_curpri
	strb	r0, [r2, r1]			// tcb_curpri[runtsk] = tinib_exepri[runtsk]
	ldr	r0, =tinib_task
	ldr	r0, [r0, r1, asl #2]		// r0 <- tinib_task[runtsk], which is the address of the function that the task first executes
	msr	cpsr, #0x5f			// enable interrupt
	bx	r0				//  jump to tinib_task[runtsk]
	
.align	4
//////////////////////////////////////////////////////////////////////////////////////////////
//    exit_and_dispatch:
//       this is called from TerminateTask() and ChainTask(), when one task relinquishes CPU
//       and another task is scheduled and dispatched
//             if (PostTaskHook != 0) PosTaskHook();
//             continue on to "start_dispatch"
///////////////////////////////////////////////////////////////////////////////////////////////
.func exit_and_dispatch
exit_and_dispatch:
dispatcher:
	ldr	r0, =PostTaskHook
	cmp	r0, #0
	beq	start_dispatch
	bl	call_posttaskhook
	//   fall  to start_dispatch
.endfunc
	
/////////////////////////////////////////////////////////////////////////////////////////////////
//    start_dispatch:
//       this function is called to dispatch schedtsk (the task that the scheduler has just selected)
//          set schedtsk to runtsk
//          if (runtsk == INVALID_TASK) jump to "pre_idle"
//          restore sp from tcxb_sp[runtsk] 
//          if  (PreTaskHook != 0) call_pretaskhook()
//          continue on to dispatch_task
//////////////////////////////////////////////////////////////////////////////////////////////////
.func start_dispatch
start_dispatch:
	ldr	r0, =schedtsk			// runtsk = schedtsk
	ldrb	r0, [r0]
	ldr	r1, =runtsk
	strb	r0, [r1]
	
	cmp	r0, #INVALID_TASK		// if (runtsk == INVALID) jump to "pre_idle"
	beq	pre_idle
	
	ldr	r1, =tcxb_sp			// sp = tcxb_sp[runtsk]
	ldr	sp, [r1,r0, asl #2]

	ldr	r0, =PreTaskHook		// if (PreTaskHook !=0) call_pretaskhook()
	cmp	r0, #0
	beq	dispatch_task
	bl	call_pretaskhook
	// fall to "dispatch_task"
.endfunc
	
/////////////////////////////////////////////////////////////////////////////////////////////////////
//   dispatch_task:  this is called only from start_dispatch 
//       dispatch to the locatoin saved in tcxb_pc[runtsk]
///////////////////////////////////////////////////////////////////////////////////////////////////
dispatch_task:
	ldr	r0, =tcxb_pc
	ldr	r1, =runtsk
	ldrb	r1, [r1]
	ldr	r0, [r0, r1, asl #2]
	bx	r0

//////////////////////////////////////////////////////////////////////////////////////////////////////
//     pre_idle:
//        switch the stack from a task stack to the "system_stack"
//        callevel = TCL_ISR2 (type2 interrupt level)
//        fall to idle_loop
///////////////////////////////////////////////////////////////////////////////////////////////////////
pre_idle:
	ldr	sp, =__system_stack__
	bic	sp, sp, #7			// make sure it is 8-byte aligned
	ldr	r0, =callevel
	mov	r1, #TCL_ISR2
	strb	r1, [r0]
	// fall to idle_loop
	
///////////////////////////////////////////////////////////////////////////////////////////////////////
//  idle_loop:
//     the body of the idle task
//         enable interrupt
//         wait  for a while  (wait for an interrupt to arrive)
//         disable interupt
//         if (schedtsk == INVALID)  jump back to "idle_loop"
//         callevel = TCS_TASK
//         jump to "start_dispatch"
///////////////////////////////////////////////////////////////////////////////////////////////////////
idle_loop:
	msr	cpsr, #0x5F			// enable interrupt
	b	next1				// wait for a while
next1:
	b	next2
next2:
	b	next3
next3:
	msr	cpsr, #0xDF			// disable interrupt
	mov	r0, #INVALID_TASK		// if (schedtsk == INVALID) jump back to "idle_loop"
	ldr	r1, =schedtsk
	ldrb	r1, [r1]		
	cmp	r0, r1
	beq	idle_loop
	mov	r0, #TCL_TASK			//  callevel = TCL_TASK
	ldr	r1, =callevel
	strb	r0, [r1]
	b	start_dispatch			// jump to "start_dispatch"

/////////////////////////////////////////////////////////////////////////////////////////////////
//     ret_int:
//       when an interrupt handler  finds relation (runtsk != schedtsk) right before
//       it returns (that is, the scheduler has run in the execution
//       of the C handler), it jumps to this function, instead of returing to
//       the interrupted context
//         precondition:  the destructive registers of the old task have been saved
//             save the non-destructive registers
//             save sp in the sp saving area in the old task's TCB
//             save "ret_int_r" in the pc saving area in the old task's TCB
//             jump to "dispatcher"
///////////////////////////////////////////////////////////////////////////////////////////////////
ret_int:
	stmfd	sp!, {r4-r7}			// save remaining nondestructive regs
	ldr	r0, =runtsk			//  tcxb_sp[runtsk] = sp
	ldrb	r0, [r0]
	ldr	r1, =tcxb_sp
	str	sp, [r1, r0, asl #2]
	ldr	r1, =tcxb_pc			// tcxb_pc[runtsk] = "ret_int_r"
	ldr	r2, =ret_int_r
	str	r2, [r1, r0, asl #2]
	b	dispatcher			// jump to "dispatcher"

//////////////////////////////////////////////////////////////////////////////////////////////////
//   ret_int_r:
//      If a task is preempted in an interrupt handler (e.g., the handler
//      called SetResource to awaken a higher priority task), 
//      the task starts with this function when it is scheduled again
//          restore the non-destructive registers
//          jump to "int_return"
//////////////////////////////////////////////////////////////////////////////////////////////////
ret_int_r:
	ldmfd	sp!, {r4-r7}			// restore non destructive registers
	b	int_return

///////////////////////////////////////////////////////////////////////////////////////////////////
//  _interrupt:
//       this is called from macro "irq_wrapper_type2"
//       the following registers hold the context values
//           r8:  runisr of the interrupted context
//           r9:   sp of the interrupted context
//           r10: callevel of the interrupted context
//           r11: the address of the high-level (in C) interrupt handler to call
//          if (callevel == TCL_TASK) {
//                // this interrupt arrives when a task (or a task + (type1 int)* )   run   
//                save sp in r9 and set sp to the bottom of the system stack
//            }
//            /*fall to "int_from_int"*/
//////////////////////////////////////////////////////////////////////////////////////////////////////     
.func _interrupt
_interrupt:
	ldr	r1, =callevel
	ldrb	r1, [r1]
	cmp	r1, #TCL_TASK
	bne	int_from_int
	mov	r9, sp		// save sp in r9
	ldr	sp, =__system_stack__
	bic	sp, sp, #7
.endfunc

//////////////////////////////////////////////////////////////////////////////////////////////////////
//  int_from_int:
//    it calls C function
//       save callevel in r10 and update callevel to TCL_ISR2
//       enable interrupt
//       call the C function
//       disable interrupt
//       restore callevel
//       restore runisr
//       if (restored callevel == TCL_TASK) {
//           restore sp from r9
//           if (shcedtsk != runtsk)  goto "ret_int"
//       }
//      // fall to int_return
/////////////////////////////////////////////////////////////////////////////////////////////////////
int_from_int:
	mov	r10, r1		// save call level in r10
	ldr	r1, =callevel	// update callevel to TCL_ISR2
	mov	r2, #TCL_ISR2
	strb	r2, [r1]
	msr	cpsr, #0X5F	// enable int
	mov	lr, pc
	bx	r11		// call C function
	msr	cpsr, #0XDF	// disable int
	ldr	r1, =callevel	// restore call level
	strb	r10, [r1]
	ldr	r2, =runisr
	strb	r8, [r2]	// restore runisr
	cmp	r10, #TCL_TASK
	bne	int_return
	mov	sp, r9		// restore stack pointer
	ldr	r0, =schedtsk
	ldrb	r0, [r0]
	ldr	r1, =runtsk
	ldrb	r1, [r1]
	cmp	r0, r1
	bne	ret_int
	// fall to int_return
	
//////////////////////////////////////////////////////////////////////////////////////////////////////
//  int_return:
//     restore destructive and context value holding registers and 
//     return from the interrupt
//         write to AIC_EOICR (??  just following the leJos convention)
//         get saved spsr and lr from the system stack
//         push the recovered spsr and lr onto the irq stack
//         restore destructive and context value holding registers
//         return from the interrupt
///////////////////////////////////////////////////////////////////////////////////////////////////////
.func int_return
int_return:
	@ end of interrupt by doing a write to AIC_EOICR
	@ just following the leJos convention
	ldr	r0, =0xFFFFF130
	str	r0,  [r0]
	
	@get spsr and lr in r0, r1
	ldmfd	sp!, {r0-r1}
	@switch to irq stack and save spsr and lr  there
	msr	cpsr, #0XD2
	stmfd	sp!, {r0-r1}
	@switch back to system stack and restore registers
	msr cpsr, #0XDF
	ldmfd	sp!, {r0-r3,r8-r11, ip, lr}
	@switch back to irq stack and return from interrupt
	msr	cpsr, #0XD2
	ldmfd	sp!, {r14}		@restore spsr
	msr	spsr, r14
	ldmfd	sp!, {pc}^		@restore pc (lr value) and cpsr (spsr value)
					@ that is, return from interrupt
.endfunc
	
.func disable_int
disable_int:
	msr	cpsr, #0xDF
	bx	lr
.endfunc
	
.func enable_int
enable_int:
	msr	cpsr, #0x5F
	bx	lr
.endfunc

.func nop	
nop:
	bx	lr
.endfunc

/* 定数の定義 */
.equ TCL_TASK , 1
.equ TCL_ISR2 , 2
.equ INVALID_TASK, 0xFF


.end
